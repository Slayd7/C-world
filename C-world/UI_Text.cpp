#include "pch.h"
#include "UI_Text.h"

UI_Text::~UI_Text()
{
	tex.Cleanup();
	if (nextLine != NULL)
		nextLine->~UI_Text();
	UIElement::~UIElement();
}

void UI_Text::Draw()
{
	Vector2D drawPos = GetAbsolutePosition();
	tex.render(drawPos.x, drawPos.y);
	if (nextLine != NULL)
		nextLine->Draw();
	UIElement::Draw();
}

bool UI_Text::HandleEvents(SDL_Event event)
{
	return false;
}

int UI_Text::GetHeight() {
	int height = h;
	if (nextLine != NULL)
	{
		height += nextLine->GetHeight();
	}
	return height;
}

int UI_Text::GetWidth() {
	int width = w;

	for (UIElement* c : children)
	{
		width += c->GetWidth();
	}
	if (nextLine != NULL)
		width = std::max(width, nextLine->GetWidth());
	return width;
}


UI_Text::UI_Text(std::string str, TEXTFLAGS flags, TTF_Font* font)
{
	int style = 0;
	SDL_Color drawColor = SDL_Color{ UI_COLOR_UINT_TO_RGBA(textPrimaryColor) };
	if (flags & TEXTFLAGS::BOLD)
	{
		style += TTF_STYLE_BOLD;
	}
	if (flags & TEXTFLAGS::ITALIC)
	{
		style += TTF_STYLE_ITALIC;
	}
	if (flags & TEXTFLAGS::COLOR_HIGHLIGHT)
	{
		drawColor = SDL_Color{ UI_COLOR_UINT_TO_RGBA(textHighlightColor) };
	}
	else if (flags & TEXTFLAGS::COLOR_SECONDARY)
	{
		drawColor = SDL_Color{ UI_COLOR_UINT_TO_RGBA(textSecondaryColor) };
	}

	TTF_SetFontStyle(font, style);

	tex.loadFromRenderedText(str, drawColor, font);
	w = tex.getWidth();
	h = tex.getHeight();
}


UI_Text* UI_Text::Parse(AssetManager* a, SDL_Renderer* r, std::string str, int size, int w, int h)
{

	/* Order of operations:
		 Split string into vector of correctly-sized strings
		 Iterate over list to find tags {
			Find location of text tag
			Since text tag indicates a change, everything before that uses previous flags
				So, create UI_Text from section BEFORE tag and remove from search string
			Set flags according to found tag
			Repeat
		}
	*/

	std::smatch m;
	std::regex x = std::regex("(\\{\/?[bhisl]\\})");
	TTF_Font* font = a->getFont(a->getFontId("basic"), size);

	char* text = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), text);
	text[str.size()] = '\0';

	char* token = NULL;
	char* iter = NULL;
	token = strtok_s(text, " ", &iter);
	int idx = 0;
	int previdx = 0;

	int width = 0;

	std::vector<std::string> lines;
	int lineHeight = 0;
	while (token != NULL)
	{	// First thing we do is check line width, and if it exceeds width, make a new line

		
		int tw, th;
		std::string regexStr(token);
		TTF_SizeText(font, (regexStr + " ").c_str(), &tw, &th);
		lineHeight = th;
		while (std::regex_search(regexStr, m, x))
		{
			int tagwidth;
			TTF_SizeText(font, m.str().c_str(), &tagwidth, nullptr);
			tw -= tagwidth;
			regexStr = regexStr.substr(m.position() +  m.length());
		}

		if (width + tw > w) // String to current index is over maximum width
		{
			lines.push_back(str.substr(previdx, (idx - previdx)));
			previdx = idx;
			width = 0;
		}
		width += tw;

		idx += strlen(token) + 1;
		token = strtok_s(NULL, " ", &iter);
	}
	lines.push_back(str.substr(previdx, (idx - previdx)));
	// At this point we have appropriately sized strings in a list
	// Tags DO count towards width unfortunately, but that's a problem for another day
	// Maybe not even a problem? Time will tell
	// Okay turns out it IS a problem, and a little bigger than I thought it would be
	// Let's throw another regex check in, it should be quick


	UI_Text* result = NULL;
	TEXTFLAGS flags = static_cast<TEXTFLAGS>(0);

	/*///////// TAGS /////////

	{b} BOLD {/b}
	{i} ITALIC {/i}
	{s} SECONDARY COLOR {/s}
	{h} HIGHLIGHT COLOR {/h}
	{l} LINK TEXT (TODO) {/l}

	/*//////////////////////*/

	for (std::string s : lines)
	{
		bool found = false;
		std::string copy = s.substr(0, s.length());
		UI_Text* txtLine = NULL;
		while (std::regex_search(copy, m, x)) {

			found = true;
			if (txtLine == NULL)
			{
				std::string c = copy.substr(0, m.position());
				if (c.size() > 0)
					txtLine = new UI_Text(c, flags, font);				
			}
			else
			{
				int tmpw = txtLine->GetWidth();
				std::string c = copy.substr(0, m.position());
				if (c.size() > 0)
				{
					UI_Text* child = new UI_Text(c, flags, font);
					txtLine->AddChild(child);
					child->Move(Vector2D(tmpw, 0));
				}
			}

			size_t idx = m.position();

			bool enable = true;
			int i = 1;
			switch (m.str()[i])
			{
			case '/':
				enable = false;
				i = 2;
				break;
			default:
				break;
			}
			switch (m.str()[i])
			{
			case 'b':
				if (enable) flags = flags | TEXTFLAGS::BOLD;
				else flags = static_cast<TEXTFLAGS>(flags & ~TEXTFLAGS::BOLD);
				break;
			case 'i':
				if (enable) flags = flags | TEXTFLAGS::ITALIC;
				else flags = static_cast<TEXTFLAGS>(flags & ~TEXTFLAGS::ITALIC);
				break;
			case 'h':
				if (enable) flags = flags | TEXTFLAGS::COLOR_HIGHLIGHT;
				else flags = static_cast<TEXTFLAGS>(flags & ~TEXTFLAGS::COLOR_HIGHLIGHT);
				break;
			case 's':
				if (enable) flags = flags | TEXTFLAGS::COLOR_SECONDARY;
				else flags = static_cast<TEXTFLAGS>(flags & ~TEXTFLAGS::COLOR_SECONDARY);
				break;

			case 'l':
				//TODO
				break;
			default:
				break;
			}
			copy = copy.substr(idx + m.length());

		}
		if (txtLine == NULL)
		{
			if (copy.size() > 0)
				txtLine = new UI_Text(copy, flags, font);
		}
		else {

			int tmpw = txtLine->GetWidth();
			if (copy.size() > 0)
			{
				UI_Text* child = new UI_Text(copy, flags, font);
				txtLine->AddChild(child);
				child->Move(Vector2D(tmpw, 0));
			}
		}
		if (result == NULL)
		{
			result = txtLine;
		}
		else {
			result->AddLine(txtLine);
			txtLine->Move(Vector2D(0, lineHeight+1));
		}
		txtLine = NULL;

	}

	return result;
}

void UI_Text::ChangeText(std::string str)
{
	if (nextLine != NULL)
	{
		nextLine->~UI_Text();
	}
}

void UI_Text::AddLine(UI_Text* next)
{
	if (nextLine != NULL)
	{
		nextLine->AddLine(next);
	}
	else
	{
		nextLine = next;
		nextLine->parent = this;
	}
}
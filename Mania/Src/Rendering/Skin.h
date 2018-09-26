#pragma once

#include "Texture.h"
#include "../Math/Vector.h"
#include "../Utils/FileReader.h"

enum SkinHeader
{
	SKIN_HEADER_GENERAL,
	SKIN_HEADER_NOTES,
	SKIN_HEADER_STAGE,
	SKIN_HEADER_ACCURACY,
	SKIN_HEADER_FONT
};

struct SkinGeneralInfo
{
	String name;
	String author;
	String originalGame;
};

enum StageAlignment
{
	STAGE_ALIGNMENT_LEFT,
	STAGE_ALIGNMENT_RIGHT,
	STAGE_ALIGNMENT_CENTER
};

struct SkinNoteInfo
{
	Texture notes[4];
	uint32 gap;
	uint32 size;
	Texture receptor;
};

struct SkinStageInfo
{
	Vector4f color;
	StageAlignment alignment;
};

struct SkinAccuracyInfo
{
	Texture miss;
	Texture bad;
	Texture good;
	Texture perfect;
	Texture marvelous;
	Texture grades[7];
};

struct SkinFontInfo
{
	Texture scoreNumbers[10];
};

struct Skin
{
	SkinGeneralInfo generalInfo;
	SkinNoteInfo noteInfo;
	SkinStageInfo stageInfo;
	SkinAccuracyInfo accuracyInfo;
	SkinFontInfo fontInfo;
};

void load_skin_from_folder(Skin* pSkin, const String& directory)
{
	FileReader skinFile(directory + "/skin.skin");
	String line;
	SkinHeader currentHeader;
	while (!(line = skinFile.ReadLine()).IsEmpty())
	{
		if (line.IsEmpty() || line.IsWhiteSpace() || line.BeginsWith("//"))
			continue;

		if (line.BeginsWith("#"))
		{
			if (line.BeginsWith("#general"))
			{
				currentHeader = SKIN_HEADER_GENERAL;
				continue;
			}
			else if (line.BeginsWith("#notes"))
			{
				currentHeader = SKIN_HEADER_NOTES;
				continue;
			}
			else if (line.BeginsWith("#stage"))
			{
				currentHeader = SKIN_HEADER_STAGE;
				continue;
			}
		}

		if (currentHeader == SKIN_HEADER_GENERAL)
		{
			String value = line.SubString(line.FindFirstOf(":") + 1);
			value = value.TrimBeginning();
			value = value.TrimEnd();

			if (line.BeginsWith("name"))
				pSkin->generalInfo.name = value;
			else if (line.BeginsWith("author"))
				pSkin->generalInfo.author = value;
		}
		else if (currentHeader == SKIN_HEADER_NOTES)
		{
			String value = line.SubString(line.FindFirstOf(":") + 1);
			value = value.TrimBeginning();
			value = value.TrimEnd();

			if (line.BeginsWith("note1"))
				pSkin->noteInfo.notes[0] = create_texture((directory + "/" + value).C_Str());
			else if (line.BeginsWith("note2"))
				pSkin->noteInfo.notes[1] = create_texture((directory + "/" + value).C_Str());
			else if (line.BeginsWith("note3"))
				pSkin->noteInfo.notes[2] = create_texture((directory + "/" + value).C_Str());
			else if (line.BeginsWith("note4"))
				pSkin->noteInfo.notes[3] = create_texture((directory + "/" + value).C_Str());
			else if (line.BeginsWith("receptor"))
				pSkin->noteInfo.receptor = create_texture((directory + "/" + value).C_Str());
			else if (line.BeginsWith("size"))
				pSkin->noteInfo.size = value.AsInteger();
			else if (line.BeginsWith("gap"))
				pSkin->noteInfo.gap = value.AsInteger();
		}
		else if (currentHeader == SKIN_HEADER_STAGE)
		{
			int32 colonIndex = line.FindFirstOf(":");
			String value = line.SubString(colonIndex + 1);
			value = value.TrimBeginning();
			value = value.TrimEnd();

			if (line.BeginsWith("alignment"))
			{
				if (value == "left")
					pSkin->stageInfo.alignment = STAGE_ALIGNMENT_LEFT;
				else if (value == "right")
					pSkin->stageInfo.alignment = STAGE_ALIGNMENT_RIGHT;
				else if (value == "center")
					pSkin->stageInfo.alignment = STAGE_ALIGNMENT_CENTER;
				else
					pSkin->stageInfo.alignment = STAGE_ALIGNMENT_LEFT;
			}
			else if (line.BeginsWith("color"))
			{
				int32 c1 = value.FindFirstOf(",");
				int32 c2 = value.FindFirstOf(",", c1 + 1);
				int32 c3 = value.FindFirstOf(",", c2 + 1);

				int32 red = value.SubString(0, c1).Trim().AsInteger();
				int32 green = value.SubString(c1 + 1, c2).Trim().AsInteger();
				int32 blue = value.SubString(c2 + 1, c3).Trim().AsInteger();
				int32 alpha = value.SubString(c3 + 1).Trim().AsInteger();

				pSkin->stageInfo.color = Vector4f(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
			}
		}
		else if (currentHeader == SKIN_HEADER_ACCURACY)
		{

		}
	}
}

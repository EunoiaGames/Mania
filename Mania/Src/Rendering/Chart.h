#pragma once

#include "../Utils/FileReader.h"

typedef uint32 TimeStamp;

struct ChartNote4K
{
	bool n1;
	bool n2;
	bool n3;
	bool n4;

	TimeStamp timeStamp;
};

typedef uint32 ms;

struct Chart
{
	String songName;
	String artistName;
	String authorName;

	String* pTags;
	uint32 numTags;

	uint32 bpm;

	std::vector< ChartNote4K > notes;
};

void load_chart(Chart* pChart, const String& chartFile)
{
	FileReader file(chartFile);
	String line;
	bool info = false;
	while (!(line = file.ReadLine()).IsEmpty())
	{
		if (line.IsEmpty() || line.IsWhiteSpace() || line.BeginsWith("//"))
			continue;

		if (line.BeginsWith("#info"))
		{
			info = true;
			continue;
		}
		else if (line.BeginsWith("#notes"))
		{
			info = false;
			continue;
		}

		if (info)
		{
			if (line.BeginsWith("song"))
			{
				pChart->songName = line.SubString(line.FindFirstOf(":") + 1).Trim();
			}
			else if (line.BeginsWith("artist"))
			{
				pChart->artistName = line.SubString(line.FindFirstOf(":") + 1).Trim();
			}
			else if (line.BeginsWith("author"))
			{
				pChart->authorName = line.SubString(line.FindFirstOf(":") + 1).Trim();
			}
			else if (line.BeginsWith("tags"))
			{
				String value = line.SubString(line.FindFirstOf(":") + 1).Trim();
				std::vector<String> tags = value.Split(",");
				pChart->numTags = tags.size();
				pChart->pTags = new String[tags.size()];
				for (uint32 i = 0; i < tags.size(); i++)
				{
					pChart->pTags[i] = tags[i].Trim();
				}
			}
			else if (line.BeginsWith("bpm"))
			{
				pChart->bpm = line.SubString(line.FindFirstOf(":") + 1).Trim().AsInteger();
			}
		}
		else
		{
			int32 colonIndex = line.FindFirstOf(":");
			int32 commaIndex1 = line.FindFirstOf(",", colonIndex + 1);
			int32 commaIndex2 = line.FindFirstOf(",", commaIndex1 + 1);
			int32 commaIndex3 = line.FindFirstOf(",", commaIndex2 + 1);

			if (colonIndex == -1)
				return;

			ChartNote4K note;
			note.timeStamp = line.SubString(0, colonIndex).Trim().AsInteger();
			note.n1 = line.SubString(colonIndex + 1, commaIndex1).Trim() == "1";
			note.n2 = line.SubString(commaIndex1 + 1, commaIndex2).Trim() == "1";
			note.n3 = line.SubString(commaIndex2 + 1, commaIndex3).Trim() == "1";
			note.n4 = line.SubString(commaIndex3 + 1).Trim() == "1";

			pChart->notes.push_back(note);
		}

		pChart->notes.shrink_to_fit();
	}
}

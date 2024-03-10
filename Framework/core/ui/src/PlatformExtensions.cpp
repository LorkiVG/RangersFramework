/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019-2023 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "../inc/PlatformExtensions.h"
#include <RmlUi/Core/Platform.h>

#pragma comment(lib, "Shlwapi.lib")
#include <RmlUi_Include_Windows.h>
#include <io.h>
#include <windows.h>
#include "Shlwapi.h"

Rml::String PlatformExtensions::FindSamplesRoot()
{
	const char* candidate_paths[] = {"", "..\\Samples\\", "..\\..\\Samples\\", "..\\..\\..\\Samples\\", "..\\..\\..\\..\\Samples\\"};

	// Fetch the path of the executable, test the candidate paths appended to that.
	char executable_file_name[MAX_PATH];
	if (GetModuleFileNameA(NULL, executable_file_name, MAX_PATH) >= MAX_PATH && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		executable_file_name[0] = 0;
	}

	Rml::String executable_path(executable_file_name);
	executable_path = executable_path.substr(0, executable_path.rfind('\\') + 1);

	// We assume we have found the correct path if we can find the lookup file from it
	const char* lookup_file = "assets\\rml.rcss";

	for (const char* relative_path : candidate_paths)
	{
		Rml::String absolute_path = executable_path + relative_path;

		if (PathFileExistsA(Rml::String(absolute_path + lookup_file).c_str()))
		{
			char canonical_path[MAX_PATH];
			if (!PathCanonicalizeA(canonical_path, absolute_path.c_str()))
				canonical_path[0] = 0;

			return Rml::String(canonical_path);
		}
	}

	return Rml::String();
}

enum class ListType { Files, Directories };

static Rml::StringList ListFilesOrDirectories(ListType type, const Rml::String& directory, const Rml::String& extension)
{
	if (directory.empty())
		return Rml::StringList();

	Rml::StringList result;

	const Rml::String find_path = directory + "/*." + (extension.empty() ? Rml::String("*") : extension);

	_finddata_t find_data;
	intptr_t find_handle = _findfirst(find_path.c_str(), &find_data);
	if (find_handle != -1)
	{
		do
		{
			if (strcmp(find_data.name, ".") == 0 || strcmp(find_data.name, "..") == 0)
				continue;

			bool is_directory = ((find_data.attrib & _A_SUBDIR) == _A_SUBDIR);
			bool is_file = (!is_directory && ((find_data.attrib & _A_NORMAL) == _A_NORMAL));

			if (((type == ListType::Files) && is_file) || ((type == ListType::Directories) && is_directory))
			{
				result.push_back(find_data.name);
			}

		} while (_findnext(find_handle, &find_data) == 0);

		_findclose(find_handle);
	}
	return result;
}

Rml::StringList PlatformExtensions::ListDirectories(const Rml::String& in_directory)
{
	return ListFilesOrDirectories(ListType::Directories, in_directory, Rml::String());
}

Rml::StringList PlatformExtensions::ListFiles(const Rml::String& in_directory, const Rml::String& extension)
{
	return ListFilesOrDirectories(ListType::Files, in_directory, extension);
}

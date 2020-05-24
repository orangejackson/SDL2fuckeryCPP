// ResourcePacker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <filesystem>

// [type]       [#bytes] [bytes] [desc]
// uint32_t     4        0-3     number of files
// uint32_t     4        4-7     starting byte of file 1
// uint32_t     4        8-11    starting byte of file 2
// uint32_t     4        12-15   starting byte of file 3
// ...
// 

enum eResType : uint8_t
{
    RES_BMP,
    RES_WAV,
    RES_TEXT,
};

std::vector<std::filesystem::path> getFileList(std::string strDirPath)
{
    std::vector<std::filesystem::path> vFilePaths;

    for(auto p : std::filesystem::directory_iterator(strDirPath))
    {
        if(!std::filesystem::is_empty(p))
        {
            vFilePaths.push_back(p.path());
        }
    }

    return vFilePaths;
}

void getFileSize()
{
}



int main(int argc, char** argv)
{
    std::vector<std::filesystem::path> vFilePaths = getFileList(R"(D:\OneDrive\Programming\Visual Studio Working Dir\Solutions\SDLTutorial\Resources)");
    uint32_t iNumFiles = vFilePaths.size();
    uint32_t iDataSize = 0;
    
    for(std::vector<std::filesystem::path>::iterator it = vFilePaths.begin();it != vFilePaths.end();++it)
    {
        std::cout << *it << std::endl;
        iDataSize += std::filesystem::file_size(*it);
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

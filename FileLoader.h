#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <dirent.h>
#include <errno.h>


using namespace std;

class FileLoader
{
private:
    unsigned char isFile;
    unsigned char isFolder;
    vector<string> validExtensions;

    int CheckFolderFile(vector<string> &folders);
    int GetFilesInFolders(vector<string> &folders, map<string, vector<string> > &foldersFiles );
public:
    int GetFiles(string dir, vector<string> &files);
    int GetFolders(string dir, vector<string> &folders);
    int SetPosSamples(vector<string> &folders, map<string, vector<string> > &foldersFiles );
    int get_each_map_size(string key, map<string, int> &foldersFiles);
    int print_map_size(map<string, vector<string> > &foldersFiles);
    int print_map(map<string, vector<string> > &foldersFiles);
    string GetFolderHeader(string dir);
    string GetFileHeader(string dir);
    FileLoader();
};

#endif // FILELOADER_H

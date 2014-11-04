#include "FileLoader.h"


static string toLowerCase(const string &in)
{
    string t;
    for (string::const_iterator i = in.begin(); i != in.end(); ++i) {
        t += tolower(*i);
    }
    return t;
}

FileLoader::FileLoader()
{
    /* Initial valid extensions */
    validExtensions.push_back("jpg");
    validExtensions.push_back("png");
    validExtensions.push_back("xml");
    validExtensions.push_back("dat");
    /* Initial Code of Folder and File */
    isFile =0x8;
    isFolder =0x4;
}
int FileLoader::CheckFolderFile(vector<string> &folders)
{
    return 0;
}

int FileLoader::GetFilesInFolders(vector<string> &folders,
                                  map<string, vector<string> > &foldersFiles )
{
    return 0;
}
int FileLoader::get_each_map_size(string key, map<string, int> &foldersFiles)
{
    return foldersFiles.find(key)->second;
}
int FileLoader::print_map_size(map<string, vector<string> > &foldersFiles)
{
    int num_of_plate = 0;
    for( map<string, vector<string> >::const_iterator ptr = foldersFiles.begin() ;
         ptr != foldersFiles.end() ; ptr++)
    {
        vector<string>::const_iterator eptr = ptr->second.begin();
        num_of_plate += ptr->second.size();
    }
    return num_of_plate;
}
int FileLoader::print_map(map<string, vector<string> > &foldersFiles)
{
    /* Travel the map */
    for( map<string, vector<string> >::const_iterator ptr = foldersFiles.begin() ;
         ptr != foldersFiles.end() ; ptr++)
    {
        cout << ptr->first << ": ";
        for( vector<string>::const_iterator eptr = ptr->second.begin() ;
             eptr != ptr->second.end() ; eptr++)
        {
            cout << *eptr << " ";
        }
        cout << endl;
    }
    return 0;
}
int FileLoader::SetPosSamples(vector<string> &folders, map<string, vector<string> > &foldersFiles )
{
    string tmp;
    vector<string> plates;
    for ( int key = 0 ; key < folders.size() ; key++)
    {
        GetFiles(folders[key], plates);
        foldersFiles.insert(make_pair(folders[key], plates));
        plates.clear();
    }
    return 0;
}

int FileLoader::GetFiles(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    size_t extensionLocation;
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        /* On Mac ingore . .. and .DS_Store */
        if(string(dirp->d_name) == "." ||
                string(dirp->d_name) == ".." ||
                string(dirp->d_name) == ".DS_Store")
            continue;
        /* Check is Folder or File */
        if ( dirp->d_type == isFile )
        {
            /* Assume the last point marks beginning of extension like file.ext */
            extensionLocation = string(dirp->d_name).find_last_of(".");
            /* Check if extension is matching the wanted ones */

            string tempExt = toLowerCase(string(dirp->d_name).substr(extensionLocation + 1));
            if (find(validExtensions.begin(), validExtensions.end(), tempExt) != validExtensions.end())
            {
//                cout << "Found matching data file: " << dir + "/" + dirp->d_name << endl;
                files.push_back(string(dir + "/" + dirp->d_name));
            }
            else
            {
                cout << "Found file does not match required file type, skipping: " << dirp->d_name << endl;
            }
            //            cout << "Find File: " + dir + "/" + dirp->d_name << " push_back to vector" << endl;
            //            folders.push_back(string(dir + "/" + dirp->d_name));
        }
    }
    closedir(dp);
    return 0;
}

int FileLoader::GetFolders(string dir, vector<string> &folders)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        /* On Mac ingore . .. and .DS_Store */
        if(string(dirp->d_name) == "." ||
                string(dirp->d_name) == ".." ||
                string(dirp->d_name) == ".DS_Store")
            continue;
        /* Check is Folder or File */
        if ( dirp->d_type == isFolder )
        {
//            cout << "Find Folder: " + dir + "/" + dirp->d_name << " push_back to vector" << endl;
            folders.push_back(string(dir + "/" + dirp->d_name));
        }
    }
    closedir(dp);
    return 0;
}
string FileLoader::GetFolderHeader(string dir)
{
    int last_mask = dir.find_last_of("/");
    return dir.substr(last_mask + 1);
}
string FileLoader::GetFileHeader(string dir)
{
    int last_mask = dir.find_last_of("/");
    int last_dot = dir.find_last_of(".");
    int lenght = last_dot - last_mask - 1;
    return dir.substr(last_mask + 1, lenght);
}

#include <map>
#include <string>
#include <taglib/fileref.h>

using namespace std;

map<string, string> get_exif_data(string file_path);

bool set_exif_data(string file_path, map<string, string> &new_exif);
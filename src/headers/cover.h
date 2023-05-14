#include <iostream>
#include <cstdlib>
#include <napi.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/attachedpictureframe.h>

using namespace std;

class Cover
{
private:
    static bool __extract_cover_art(string file_path, string cover_art_dest);
    inline static const char *picture_id = "APIC";

public:
    static Napi::Boolean extract_cover_art(const Napi::CallbackInfo &info);
};
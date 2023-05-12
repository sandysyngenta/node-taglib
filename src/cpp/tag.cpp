#include "include/tag.h"

map<string, string> get_exif_data(string file_path)
{
    std::map<string, string> map;
    TagLib::FileRef f = TagLib::FileRef(file_path.c_str());
    auto tag = f.tag();
    auto album = tag->album();
    auto artist = tag->artist();
    auto comment = tag->comment();
    auto genre = tag->genre();
    auto title = tag->title();
    map["album"] = album.isNull() ? "" : album.to8Bit();
    map["artist"] = artist.isNull() ? "" : artist.to8Bit();
    map["comment"] = comment.isNull() ? "" : comment.to8Bit();
    map["genre"] = genre.isNull() ? "" : genre.to8Bit();
    map["title"] = title.isNull() ? "" : title.to8Bit();
    map["track"] = to_string(tag->track());
    map["year"] = to_string(tag->year());
    return map;
}
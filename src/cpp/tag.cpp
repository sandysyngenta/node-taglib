#include "include/tag.h"

void set_exif(TagLib::Tag *tag, string key, string data) {
    if(key == "album")
        tag->setAlbum(data.c_str());
    else if(key == "artist")
        tag->setArtist(data.c_str());
    else if(key == "comment")
        tag->setComment(data.c_str());
    else if(key == "genre")
        tag->setGenre(data.c_str());
    else if(key == "title")
        tag->setTitle(data.c_str());
    else if(key == "track")
        tag->setTrack(stoi(data));
    else if(key == "year")
        tag->setYear(stoi(data));
}

/*
 *   Extracts the audio meta-data from the the given file.
*/
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

/*
 *   Writes new exif data to the given audio file.
*/
bool set_exif_data(string file_path, map<string, string> &new_exif) {
    TagLib::FileRef f = TagLib::FileRef(file_path.c_str());
    auto tag = f.tag();
    for(auto i = new_exif.begin(); i != new_exif.end(); i++) {
        set_exif(tag, i->first, i->second);
    }
    return f.save();
}
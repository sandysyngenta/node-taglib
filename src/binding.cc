#include "headers/exif.h"
#include "headers/cover.h"

Napi::Object init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        "getExifData",
        Napi::Function::New(env, Exif::get_exif_data));
    exports.Set(
        "setExifData",
        Napi::Function::New(env, Exif::set_exif_data));
    exports.Set(
        "extractCoverArt",
        Napi::Function::New(env, Cover::extract_cover_art));
    return exports;
}

NODE_API_MODULE(node_taglib, init);
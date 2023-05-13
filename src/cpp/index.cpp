#include <napi.h>
#include <iostream>
#include "include/tag.h"

// export this function to js-side.
Napi::Object getExifData(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if(info.Length() <= 0)
        Napi::TypeError::New(env, "Err: node-taglib getExifData expects one argument as filepath.").ThrowAsJavaScriptException();
    if(!info[0].IsString())
        Napi::TypeError::New(env, "Err: node-taglib: getExifData expects argument of type string.").ThrowAsJavaScriptException();
    string file_path = info[0].ToString();
    auto map = get_exif_data(file_path);
    Napi::Object ret_obj = Napi::Object::New(env);
    for(auto i = map.begin(); i != map.end(); i++) {
        ret_obj.Set(i->first, Napi::String::New(env, i->second));
    }
    return ret_obj;
}

Napi::Boolean setExifData(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if(info.Length() < 2)
        Napi::TypeError::New(env, "Err: node-taglib setExifData expects two argument.").ThrowAsJavaScriptException();
    if(!info[0].IsString())
        Napi::TypeError::New(env, "Err: node-taglib: setExifData expects 1st argument of type string.").ThrowAsJavaScriptException();
    if(!info[1].IsObject())
        Napi::TypeError::New(env, "Err: node-taglib: setExifData expects 2nd argument of type object.").ThrowAsJavaScriptException();
    string file_path = info[0].ToString();
    auto new_exif_data = info[1].ToObject();
    string exif_keys[] = {"album", "artist", "comment", "genre", "title", "track", "year"};
    map<string, string> map;
    for(string key : exif_keys) {
        if(!new_exif_data.Get(key).IsUndefined())
            map[key] = new_exif_data.Get(key).ToString();
    }
    return Napi::Boolean::New(env, set_exif_data(file_path, map));
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        "getExifData",
        Napi::Function::New(env, getExifData)
    );
    exports.Set(
        "setExifData",
        Napi::Function::New(env, setExifData)
    );
    return exports;
}

NODE_API_MODULE(node_taglib, init);
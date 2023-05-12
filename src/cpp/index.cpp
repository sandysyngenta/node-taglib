#include <napi.h>
#include <iostream>
#include "include/tag.h"

// export this function to js-side.
Napi::Object getExifData(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if(info.Length() <= 0)
        Napi::TypeError::New(env, "Err: node-taglib getExifData expects one argument as filepath").ThrowAsJavaScriptException();
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

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        "getExifData",
        Napi::Function::New(env, getExifData)
    );
    return exports;
}

NODE_API_MODULE(node_taglib, init);
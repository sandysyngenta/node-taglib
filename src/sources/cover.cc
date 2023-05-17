#include "../headers/cover.h"

void Cover::__get_cover_data_byte(string file_path, Cover_Info *cover_info)
{
    TagLib::MPEG::File mpeg_file(file_path.c_str());
    TagLib::ID3v2::Tag *id3v2_tag = mpeg_file.ID3v2Tag();
    if (id3v2_tag)
    {
        TagLib::ID3v2::FrameList frame_list;
        TagLib::ID3v2::AttachedPictureFrame *pic_frame;
        frame_list = id3v2_tag->frameListMap()[Cover::picture_id];
        if (!frame_list.isEmpty())
        {
            for (auto it = frame_list.begin(); it != frame_list.end(); ++it)
            {
                pic_frame = (TagLib::ID3v2::AttachedPictureFrame *)(*it);
                if (pic_frame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
                {
                    if (pic_frame->picture().size() > 0)
                    {
                        cover_info->size = pic_frame->picture().size();
                        cover_info->cover_art_data = new char[cover_info->size]();
                        memcpy(cover_info->cover_art_data, pic_frame->picture().data(), cover_info->size);
                    }
                }
            }
        }
    }
}

bool Cover::__save_cover_art(string file_path, string cover_art_dest)
{
    Cover_Info info;
    __get_cover_data_byte(file_path, &info);
    const bool has_cover_art = info.cover_art_data != nullptr && info.size > 0;
    if (has_cover_art)
    {
        FILE *file = fopen(cover_art_dest.c_str(), "wb");
        fwrite(info.cover_art_data, info.size, 1, file);
        fclose(file);
    }
    return has_cover_art;
}

Napi::Boolean Cover::save_cover_art(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2)
        Napi::TypeError::New(env, "Err: node-taglib saveCoverArt expects two argument.").ThrowAsJavaScriptException();
    if (!info[0].IsString())
        Napi::TypeError::New(env, "Err: node-taglib saveCoverArt expects 1st argument of type string.").ThrowAsJavaScriptException();
    if (!info[1].IsString())
        Napi::TypeError::New(env, "Err: node-taglib saveCoverArt expects 2nd argument of type string.").ThrowAsJavaScriptException();
    string file_path = info[0].ToString();
    string cover_art_dest = info[1].ToString();
    return Napi::Boolean::New(env, Cover::__save_cover_art(file_path, cover_art_dest));
}

Napi::Buffer<uint8_t> Cover::get_cover_art(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1)
        Napi::TypeError::New(env, "Err: node-taglib getCoverArt expects 1 argument.").ThrowAsJavaScriptException();
    if (!info[0].IsString())
        Napi::TypeError::New(env, "Err: node-taglib getCoverArt expects argument of type string.").ThrowAsJavaScriptException();
    string file_path = info[0].ToString();
    Cover_Info cover_info;
    __get_cover_data_byte(file_path, &cover_info);
    uint8_t *buffer = (uint8_t *) cover_info.cover_art_data;
    return Napi::Buffer<uint8_t>::New(env, buffer, cover_info.size);
}
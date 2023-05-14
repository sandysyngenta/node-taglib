#include "../headers/cover.h"

bool Cover::__extract_cover_art(string file_path, string cover_art_dest)
{
    bool has_cover_art = false;
    TagLib::MPEG::File mpeg_file(file_path.c_str());
    TagLib::ID3v2::Tag *id3v2_tag = mpeg_file.ID3v2Tag();
    if (id3v2_tag)
    {
        TagLib::ID3v2::FrameList frame_list;
        TagLib::ID3v2::AttachedPictureFrame *pic_frame;
        void *source_image;
        unsigned long size;
        frame_list = id3v2_tag->frameListMap()[Cover::picture_id];
        if (!frame_list.isEmpty())
        {
            for (auto it = frame_list.begin(); it != frame_list.end(); ++it)
            {
                pic_frame = (TagLib::ID3v2::AttachedPictureFrame *)(*it);
                if (pic_frame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
                {
                    size = pic_frame->picture().size();
                    source_image = malloc(size);
                    if (source_image)
                    {
                        FILE *file = fopen(cover_art_dest.c_str(), "wb");
                        memcpy(source_image, pic_frame->picture().data(), size);
                        fwrite(source_image, size, 1, file);
                        fclose(file);
                        free(source_image);
                        has_cover_art = true;
                    }
                }
            }
        }
    }
    return has_cover_art;
}

Napi::Boolean Cover::extract_cover_art(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if(info.Length() < 2)
        Napi::TypeError::New(env, "Err: node-taglib extractCoverArt expects two argument.").ThrowAsJavaScriptException();
    if(!info[0].IsString())
        Napi::TypeError::New(env, "Err: node-taglib extractCoverArt expects 1st argument of type string.").ThrowAsJavaScriptException();
    if(!info[1].IsString())
        Napi::TypeError::New(env, "Err: node-taglib extractCoverArt expects 2nd argument of type string.").ThrowAsJavaScriptException();
    string file_path = info[0].ToString();
    string cover_art_dest = info[1].ToString();
    return Napi::Boolean::New(env, Cover::__extract_cover_art(file_path, cover_art_dest));
}
>**Warning**
>Development Phase.
>macOS & linux support only.
> adding support for windows as well.

### Node.js binding for taglib. ``Still in development phase``.

##### TagLib is a ``C++`` library for reading and editing the metadata of several popular audio formats. To know more click [here](https://taglib.org/).

How to run--

1. Build the project run- ``npm run build`` or ``yarn build``.
2. Open ``index.js`` file set ``demoFile`` to any valid audio file path (ex- mp3).
3. ``npm start``.

you will see the exif data of that file.

>**Note**
>Don't worry about file & folder structure for now. All will be fixed in near future.

### Bindings to be written

- [x] Get exif data.
- [x] Set / Update exif data.
- [ ] Extract cover image.
- [ ] many more features coming soon...
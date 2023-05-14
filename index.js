const node_taglib = require("bindings")("node_taglib");

/**
 * This method extracts the exif metadata from the given file.
 * @param {string} filePath path of the media file.
 * @returns {{
 *      album: string,
 *      artist: string,
 *      genre: string,
 *      title: string,
 *      comment: string,
 *      track: string,
 *      year: string,
 * }}
 */
function getExifData(filePath) {
  return node_taglib.getExifData(filePath);
}

/**
 * This method update / create the exif data on the given file.
 * @param {string} filePath path of the media file.
 * @param {{
 *      album: string | undefined,
 *      artist: string  | undefined,
 *      genre: string  | undefined,
 *      title: string  | undefined,
 *      comment: string  | undefined,
 *      track: string  | undefined,
 *      year: string  | undefined,
 * }} exifObject exif metadata keys to update.
 * @returns {boolean}
 */
function setExifData(filePath, exifObject) {
  return node_taglib.setExifData(filePath, exifObject);
}

/**
 * This method extracts the cover art image if exists from the given file,
 * and saves it to the destination.
 * @param {string} filePath path of the media file.
 * @param {string} destinationFile destination path to save the cover art.
 * @returns {boolean}
 */
function extractCoverArt(filePath, destinationFile) {
  return node_taglib.extractCoverArt(filePath, destinationFile);
}

const NodeTagLib = {
  getExifData,
  setExifData,
  extractCoverArt,
};

module.exports = NodeTagLib;

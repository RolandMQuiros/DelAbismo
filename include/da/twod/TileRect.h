/**
 * Superclass for every object that is a rectangle subdivided into tiles.
 */

#ifndef DA_TILERECT_H
#define DA_TILERECT_H

namespace da {
    
class TileRect {
public:
    /**Construct a TileRect with the given dimensions
     * @param widthInTiles width of the rectangle in tiles
     * @param heightInTiles height of the rectangle in tiles
     * @param tileWidth width of a tile in pixels
     * @param tileHeight height of a tile in pixels
     */
    TileRect(unsigned int widthInTiles=0, unsigned int heightInTiles=0,
             unsigned int tileWidth=0, unsigned int tileHeight=0);
    /**Construct a TileRect from another TileRect
     * @param other TileRect to copy
     */
    TileRect(const TileRect &other);
    /**Assign a TileRect copy
     * @param other TileRect to copy
     * @return reference to new TileRect copy
     */
    TileRect &operator=(const TileRect &other);
    /**Re-dimension TileRect
     * @param widthInTiles width of the rectangle in tiles
     * @param heightInTiles height of the rectangle in tiles
     * @param tileWidth width of a tile in pixels
     * @param tileHeight height of a tile in pixels
     */
    void redim(unsigned int widthInTiles, unsigned int heightInTiles,
               unsigned int tileWidth, unsigned int tileHeight);

    /** Get width in pixels.
     * @return width in pixels
     */
    unsigned int getWidth() const;
    /** Get height in pixels
     * @return height in pixels
     */
    unsigned int getHeight() const;
    /** Get tile width
     * @return tile width
     */
    unsigned int getTileWidth() const;
    /** Get tile height
     * @return tile height
     */
    unsigned int getTileHeight() const;
    /** Get width in tiles
     * @return width in tiles
     */
    unsigned int getWidthInTiles() const;
    /** Get height in tiles
     * @return height in tiles
     */
    unsigned int getHeightInTiles() const;
    /** Get number of tiles
     * @return number of tiles
     */
    unsigned int getSizeInTiles() const;
    /**Convert a row-column pair to a linear index
     * @param row
     * @param col
     * @return 
     */
    unsigned int rowColToIndex(unsigned int row, unsigned int col) const;
    void indexToRowCol(int index, int &row, int &col) const;
    
    static void indexToRowCol(int index, int width, int &row, int &col);
    static unsigned int rowColToIndex(unsigned int row, unsigned int col,
                                      unsigned int width,
                                      unsigned int height);
protected:
    unsigned int mpWidth;
    unsigned int mpHeight;
    unsigned int mpTileWidth;
    unsigned int mpTileHeight;

    unsigned int mpWidthInTiles;
    unsigned int mpHeightInTiles;
    unsigned int mpSizeInTiles;
};

}

#endif

/* 
 * File:   ContentManager.h
 * Author: rquiros
 *
 * Created on January 7, 2012, 4:48 PM
 */

#ifndef DA_CONTENTMANAGER_H
#define	DA_CONTENTMANAGER_H

#include "da/ContentTypes.h"

namespace da {

class ContentManager {
public:
    /**Load a resource from a file on the hard drive
     * Loads a file into the cache.  Future calls to Load(string) will look up
     * the path string in a tree map and return the contents.
     * 
     * Additionally, every time a new resource is loaded into the cache, the
     * ContentManager will search for unused resources and remove them.
     * @param source path to file
     * @return reference to resource
     */
    template<class Resource>
    std::shared_ptr<Resource> load(const std::string &source);
    /**Load a resource from a position in memory
     * @param key identification key for future access
     * @param data position in memory
     * @param sizeInBytes size of resource
     * @return reference to resource
     */
    template<class Resource>
    std::shared_ptr<Resource> load(const std::string &key,
                                        const char *data,
                                        std::size_t sizeInBytes);
private:
    std::map<std::string, TexturePtr> mvTextures;
    std::map<std::string, FontPtr> mvFonts;
    std::map<std::string, SoundBufferPtr> mvSoundBuffers;
};

}

#endif	/* CONTENTMANAGER_H */


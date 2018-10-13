////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Index.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE/Index.hpp>

#include <Library/Core/Containers/Dictionary.hpp>
#include <Library/Core/Containers/Object.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Index&                      anIndex                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Index") ;

    library::core::utils::Print::Line(anOutputStream) << "Timestamp:" << (anIndex.timestamp_.isDefined() ? anIndex.timestamp_.toString() : "Undefined") ;

    for (const auto& itemMapIt : anIndex.itemMap_)
    {

        library::core::utils::Print::Separator(anOutputStream, Kernel::StringFromType(itemMapIt.first)) ;

        for (const auto& itemMapItIt : itemMapIt.second)
        {
            library::core::utils::Print::Line(anOutputStream) << (itemMapItIt.first + ":") << itemMapItIt.second.toString() ;
        }

    }

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Index::isEmpty                              ( ) const
{
    return itemMap_.empty() ;
}

Instant                         Index::getTimestamp                         ( ) const
{
    return timestamp_ ;
}

URL                             Index::getRemoteUrlOfKernel                 (   const   Kernel&                     aKernel                                     ) const
{

    if (!aKernel.isDefined())
    {
        throw library::core::error::runtime::Undefined("Kernel") ;
    }

    const auto itemMapIt = itemMap_.find(aKernel.getType()) ;

    if (itemMapIt != itemMap_.end())
    {

        const auto itemMapItIt = itemMapIt->second.find(aKernel.getName()) ;

        if (itemMapItIt != itemMapIt->second.end())
        {
            return itemMapItIt->second + aKernel.getName() ;
        }

    }

    return URL::Undefined() ;

}

Array<URL>                      Index::findRemoteUrls                       (   const   std::regex&                 aKernelNameRegex                            ) const
{

    Array<URL> urls = Array<URL>::Empty() ;

    for (const auto& itemMapIt : itemMap_)
    {

        for (const auto& itemMapItIt : itemMapIt.second)
        {

            if (itemMapItIt.first.match(aKernelNameRegex))
            {

                const URL url = itemMapItIt.second + itemMapItIt.first ;

                urls.add(url) ;

            }

        }

    }

    return urls ;

}

Index                           Index::Empty                                ( )
{
    return {} ;
}

Index                           Index::Load                                 (   const   File&                       aFile                                       )
{

    using library::core::ctnr::Object ;
    using library::core::ctnr::Dictionary ;

    if (!aFile.exists())
    {
        throw library::core::error::RuntimeError("File [{}] does not exist.", aFile.toString()) ;
    }

    Index index ;

    index.timestamp_ = Instant::Now() ; // [TBM] This should be replaced with the index file creation time

    const Dictionary indexDictionary = Object::Load(aFile, Object::Format::JSON).getDictionary() ;

    for (const auto& indexDictionaryItem : indexDictionary)
    {

        const String kernelTypeString = indexDictionaryItem.accessKey() ;

        const Kernel::Type kernelType = Kernel::TypeFromString(kernelTypeString) ;

        for (const auto& kernelTypeItem : indexDictionaryItem.accessValue().getDictionary())
        {

            const String kernelName = kernelTypeItem.accessKey() ;
            const URL remoteUrl = URL::Parse(kernelTypeItem.accessValue().getString()) ;

            if (index.itemMap_.find(kernelType) == index.itemMap_.end())
            {
                index.itemMap_[kernelType] = Map<String, URL>() ;
            }

            index.itemMap_[kernelType].emplace(kernelName, remoteUrl) ;

        }
        
    }

    return index ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Index::Index                                ( )
                                :   timestamp_(Instant::Undefined())
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
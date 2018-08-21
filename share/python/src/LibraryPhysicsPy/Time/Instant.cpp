////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/Instant.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Instant.hpp>

#include <boost/python/stl_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Container>
struct ToListConverter
{

	static PyObject*            convert                                     (   const   Container&                  aContainer                                  )
    {
		
        boost::python::list list ;

        for (const auto& element : aContainer)
        {
            list.append(element) ;
        }
		
        return boost::python::incref(list.ptr()) ;

	}

} ;

struct IterableConverter
{

    /// @brief                  Registers converter from a python interable type to the provided type
  
                                template <typename Container>
    IterableConverter&          from_python                                 ( )
    {

        boost::python::converter::registry::push_back
        (
            &IterableConverter::convertible,
            &IterableConverter::construct<Container>,
            boost::python::type_id<Container>()
        ) ;

        return *this ;

    }

    /// @brief                  Registers converter from the provided type to a python interable type
  
                                template <typename Container>
    IterableConverter&          to_python                                   ( )
    {

        boost::python::to_python_converter<Container, ToListConverter<Container>>() ;

        return *this ;

    }

    /// @brief                  Check if PyObject is iterable

    static void*                convertible                                 (           PyObject*                   anObject                                    )
    {
    return PyObject_GetIter(anObject) ? anObject : nullptr ;
    }

    /// @brief Convert iterable PyObject to C++ container type.
    ///
    /// Container Concept requirements:
    ///
    ///   * Container::value_type is CopyConstructable.
    ///   * Container can be constructed and populated with two iterators.
    ///     I.e. Container(begin, end)

                                template <typename Container>
    static void                 construct                                   (           PyObject*                   object,
                                                                                        boost::python::converter::rvalue_from_python_stage1_data* data          )
    {

        namespace python = boost::python ;

        // Object is a borrowed reference, so create a handle indicting it is borrowed for proper reference counting

        python::handle<> handle(python::borrowed(object)) ;

        // Obtain a handle to the memory block that the converter has allocated for the C++ type

        typedef python::converter::rvalue_from_python_storage<Container> storage_type ;
        
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes ;

        typedef python::stl_input_iterator<typename Container::value_type> iterator ;

        // Allocate the C++ type into the converter's memory block, and assign
        // its handle to the converter's convertible variable.  The C++
        // container is populated by passing the begin and end iterators of
        // the python object to the container's constructor.

        new (storage) Container
        (
            iterator(python::object(handle)), // begin
            iterator() // end
        ) ;
        
        data->convertible = storage ;

    }

} ;

inline void                     LibraryPhysicsPy_Time_Instant               ( )
{

    using namespace boost::python ;

    using library::physics::time::Instant ;
    using library::physics::time::Duration ;

    scope in_Instant = class_<Instant>("Instant", no_init)

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + other<Duration>())
		.def(self - other<Duration>())
		.def(self - self)
		.def(self += other<Duration>())
		.def(self -= other<Duration>())

        .def(self_ns::str(self_ns::self))
        
        .def("__repr__", +[] (const Instant& anInstant) -> std::string { return anInstant.toString() ; })

        .def("isDefined", &Instant::isDefined)
        .def("isPostEpoch", &Instant::isPostEpoch)
        
        .def("getDateTime", &Instant::getDateTime)
        .def("getJulianDate", &Instant::getJulianDate)
        .def("getModifiedJulianDate", &Instant::getModifiedJulianDate)
        .def("toString", &Instant::toString)

        .def("Undefined", &Instant::Undefined).staticmethod("Undefined")
        .def("Now", &Instant::Now).staticmethod("Now")
        .def("J2000", &Instant::J2000).staticmethod("J2000")
        .def("DateTime", &Instant::DateTime).staticmethod("DateTime")
        .def("JulianDate", &Instant::JulianDate).staticmethod("JulianDate")
        .def("ModifiedJulianDate", &Instant::ModifiedJulianDate).staticmethod("ModifiedJulianDate")

    ;

    using library::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Instant>>()
        .to_python<Array<Instant>>()
        
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
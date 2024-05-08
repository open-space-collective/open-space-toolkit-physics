/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Length(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;

    using ostk::physics::unit::Length;

    class_<Length> length(aModule, "Length",
        R"doc(
            Length.

            https://en.wikipedia.org/wiki/Length
        )doc"
    );

    length
        .def(init<Real, Length::Unit>(),
            R"doc(
                Constructor.

                Args:
                    aReal (Real): A real number.
                    aUnit (Length.Unit): A length unit.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + self)
        .def(self - self)

        .def(self += self)
        .def(self -= self)

        .def(+self)
        .def(-self)

        .def(
            "__mul__",
            [](const Length& aLength, Real aReal)
            {
                return aLength * aReal;
            },
            is_operator()
        )
        .def(
            "__truediv__",
            [](const Length& aLength, Real aReal)
            {
                return aLength / aReal;
            },
            is_operator()
        )
        .def(
            "__imul__",
            [](const Length& aLength, Real aReal)
            {
                return aLength * aReal;
            },
            is_operator()
        )
        .def(
            "__itruediv__",
            [](const Length& aLength, Real aReal)
            {
                return aLength / aReal;
            },
            is_operator()
        )

        .def("__str__", &(shiftToString<Length>))
        .def(
            "__repr__",
            +[](const Length& aLength) -> std::string
            {
                return aLength.toString();
            }
        )

        .def("is_defined", &Length::isDefined,
            R"doc(
                Check if the length is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def("is_zero", &Length::isZero,
            R"doc(
                Check if the length is zero.

                Returns:
                    bool: True if zero.
            )doc"
        )

        .def("get_unit", &Length::getUnit,
            R"doc(
                Get the length unit.

                Returns:
                    Length.Unit: The length unit.
            )doc"
        )
        .def("in_unit", &Length::in,
            R"doc(
                Get the length in a given unit.

                Returns:
                    Real: The length in the given unit.
            )doc"
        )
        .def("in_meters", &Length::inMeters,
            R"doc(
                Get the length in meters.

                Returns:
                    Real: The length in meters.
            )doc"
        )
        .def("in_kilometers", &Length::inKilometers,
            R"doc(
                Get the length in kilometers.

                Returns:
                    Real: The length in kilometers.
            )doc"
        )
        .def("to_string", &Length::toString, "aPrecision"_a = Integer::Undefined(),
            R"doc(
                Get the string representation of the length.

                Args:
                    aPrecision (int): A precision.

                Returns:
                    str: The string representation.
            )doc"
        )

        .def_static("undefined", &Length::Undefined,
            R"doc(
                Get an undefined length.

                Returns:
                    Length: An undefined length.
            )doc"
        )
        .def_static("millimeters", &Length::Millimeters,
            R"doc(
                Construct a length in millimeters.

                Returns:
                    Length: A length in millimeters.
            )doc"
        )
        .def_static("meters", &Length::Meters,
            R"doc(
                Construct a length in meters.

                Returns:
                    Length: A length in meters.
            )doc"
        )
        .def_static("kilometers", &Length::Kilometers,
            R"doc(
                Construct a length in kilometers.

                Returns:
                    Length: A length in kilometers.
            )doc"
        )
        .def_static("parse", &Length::Parse,
            R"doc(
                Parse a string and construct a length.

                Args:
                    aString (str): A string.

                Returns:
                    Length: A length.
            )doc"
        )
        .def_static("string_from_unit", &Length::StringFromUnit,
            R"doc(
                Get the string representation of a length unit.

                Returns:
                    str: The string representation.
            )doc"
        )
        .def_static("symbol_from_unit", &Length::SymbolFromUnit,
            R"doc(
                Get the symbol of a length unit.

                Returns:
                    str: The symbol.
            )doc"
        )

        ;

    enum_<Length::Unit>(length, "Unit")

        .value("Undefined", Length::Unit::Undefined,
            R"doc(
                Undefined length unit.
            )doc"
        )
        .value("Meter", Length::Unit::Meter,
            R"doc(
                Meter (SI).
            )doc"
        )
        .value("Foot", Length::Unit::Foot,
            R"doc(
                Foot.
            )doc"
        )
        .value("TerrestrialMile", Length::Unit::TerrestrialMile,
            R"doc(
                Terrestrial mile.
            )doc"
        )
        .value("NauticalMile", Length::Unit::NauticalMile,
            R"doc(
                Nautical mile.
            )doc"
        )
        .value("AstronomicalUnit", Length::Unit::AstronomicalUnit,
            R"doc(
                Astronomical Unit.
            )doc"
        )

        ;

    using ostk::mathematics::object::Interval;

    class_<Interval<Length>>(aModule, "Interval")

        .def(init<const Length&, const Length&, const Interval<Length>::Type&>(),
            R"doc(
                Constructor.

                Args:
                    aLowerBound (Length): The lower bound.
                    anUpperBound (Length): The upper bound.
                    aType (Interval.Type): The type.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("is_defined", &Interval<Length>::isDefined,
            R"doc(
                Check if the interval is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def("is_degenerate", &Interval<Length>::isDegenerate,
            R"doc(
                Check if the interval is degenerate.

                Returns:
                    bool: True if degenerate.
            )doc"
        )
        .def("intersects", &Interval<Length>::intersects,
            R"doc(
                Check if the interval intersects another interval.

                Returns:
                    bool: True if intersects.
            )doc"
        )
        .def(
            "contains_length",
            +[](const Interval<Length>& anInterval, const Length& aLength) -> bool
            {
                return anInterval.contains(aLength);
            },
            R"doc(
                Check if the interval contains a length.

                Args:
                    aLength (Length): A length.

                Returns:
                    bool: True if contains.
            )doc"
        )
        .def(
            "contains_interval",
            +[](const Interval<Length>& anInterval, const Interval<Length>& anOtherInterval) -> bool
            {
                return anInterval.contains(anOtherInterval);
            },
            R"doc(
                Check if the interval contains another interval.

                Args:
                    anOtherInterval (Interval): Another interval.

                Returns:
                    bool: True if contains.
            )doc"
        )

        .def("get_lower_bound", &Interval<Length>::getLowerBound,
            R"doc(
                Get the lower bound.

                Returns:
                    Length: The lower bound.
            )doc"
        )
        .def("get_upper_bound", &Interval<Length>::getUpperBound,
            R"doc(
                Get the upper bound.

                Returns:
                    Length: The upper bound.
            )doc"
        )

        .def_static("undefined", &Interval<Length>::Undefined,
            R"doc(
                Get an undefined interval.

                Returns:
                    Interval: An undefined interval.
            )doc"
        )
        .def_static("closed", &Interval<Length>::Closed,
            R"doc(
                Construct a closed interval.

                Returns:
                    Interval: A closed interval.
            )doc"
        )

        ;
}

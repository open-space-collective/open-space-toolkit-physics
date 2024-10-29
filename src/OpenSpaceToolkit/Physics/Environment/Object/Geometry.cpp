/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Geometry.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace object
{

Geometry::Geometry(const Geometry::Object& anObject, const Shared<const Frame>& aFrameSPtr)
    : composite_(anObject),
      frameSPtr_(aFrameSPtr)
{
}

Geometry::Geometry(const Composite& aComposite, const Shared<const Frame>& aFrameSPtr)
    : composite_(aComposite),
      frameSPtr_(aFrameSPtr)
{
}

Geometry::Geometry(const Geometry& aGeometry)
    : composite_(aGeometry.composite_),
      frameSPtr_(aGeometry.frameSPtr_)
{
}

Geometry& Geometry::operator=(const Geometry& aGeometry)
{
    if (this != &aGeometry)
    {
        composite_ = aGeometry.composite_;
        frameSPtr_ = aGeometry.frameSPtr_;
    }

    return *this;
}

bool Geometry::operator==(const Geometry& aGeometry) const
{
    if ((!this->isDefined()) || (!aGeometry.isDefined()))
    {
        return false;
    }

    return (composite_ == aGeometry.composite_) && ((*frameSPtr_) == (*aGeometry.frameSPtr_));
}

bool Geometry::operator!=(const Geometry& aGeometry) const
{
    return !((*this) == aGeometry);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Geometry& aGeometry)
{
    ostk::core::utils::Print::Header(anOutputStream, "Geometry");

    ostk::core::utils::Print::Line(anOutputStream) << "Objects:";

    aGeometry.composite_.print(anOutputStream, false);

    ostk::core::utils::Print::Line(anOutputStream)
        << "Frame:"
        << (((aGeometry.frameSPtr_ != nullptr) && aGeometry.frameSPtr_->isDefined()) ? aGeometry.frameSPtr_->getName()
                                                                                     : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Geometry::isDefined() const
{
    return composite_.isDefined() && (frameSPtr_ != nullptr) && frameSPtr_->isDefined();
}

bool Geometry::intersects(const Geometry& aGeometry) const
{
    if (!aGeometry.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if ((*frameSPtr_) == (*aGeometry.frameSPtr_))
    {
        return composite_.intersects(aGeometry.composite_);
    }

    throw ostk::core::error::runtime::ToBeImplemented("Geometry :: intersects");

    return false;
}

bool Geometry::contains(const Geometry& aGeometry) const
{
    if (!aGeometry.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if ((*frameSPtr_) == (*aGeometry.frameSPtr_))
    {
        return composite_.contains(aGeometry.composite_);
    }

    throw ostk::core::error::runtime::ToBeImplemented("Geometry :: contains");

    return false;
}

const Composite& Geometry::accessComposite() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    return composite_;
}

Shared<const Frame> Geometry::accessFrame() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    return frameSPtr_;
}

Geometry Geometry::in(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    using ostk::core::type::String;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    using ostk::physics::coordinate::Transform;

    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if ((*frameSPtr_) == (*aFrameSPtr))
    {
        return *this;
    }

    const Transform transform = frameSPtr_->getTransformTo(aFrameSPtr, anInstant);  // [TBM] Bottleneck here

    const RotationMatrix rotationMatrix = RotationMatrix::Quaternion(transform.getOrientation().toConjugate());

    const Vector3d translationVector = transform.getOrientation() * transform.getTranslation();

    const Transformation transformation =
        Transformation::Translation(translationVector) * Transformation::Rotation(rotationMatrix);

    Composite composite = composite_;

    composite.applyTransformation(transformation);

    return {composite, aFrameSPtr};
}

Geometry Geometry::intersectionWith(const Geometry& aGeometry) const
{
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    if (!aGeometry.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    Intersection intersection = Intersection::Empty();

    if ((*frameSPtr_) == (*aGeometry.frameSPtr_))
    {
        intersection = composite_.intersectionWith(aGeometry.composite_);
    }
    else
    {
        throw ostk::core::error::RuntimeError("Only same frame intersection supported at the moment.");
    }

    if (intersection.isEmpty())
    {
        return {Composite::Empty(), frameSPtr_};
    }

    return {intersection.accessComposite(), frameSPtr_};
}

Geometry Geometry::Undefined()
{
    return {Composite::Undefined(), nullptr};
}

}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk

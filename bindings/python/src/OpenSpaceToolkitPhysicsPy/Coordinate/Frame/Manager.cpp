/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::String;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::coordinate::frame::Manager;
    using ostk::physics::coordinate::Transform;
    using ostk::physics::time::Instant;

    class_<Manager> manager(
        aModule,
        "Manager",
        R"doc(
            Reference frame manager (thread-safe).

            Manages the lifecycle and caching of reference frames. This is a singleton class.

            The following environment variable can be defined:

            - "OSTK_PHYSICS_FRAME_MANAGER_MAX_TRANSFORM_CACHE_SIZE" will override the default
              maximum transform cache size (default: 1000)
        )doc"
    );

    manager

        .def(
            "has_frame_with_name",
            &Manager::hasFrameWithName,
            arg("frame_name"),
            R"doc(
                Check if a frame with the given name exists.

                Args:
                    frame_name (str): Name of the frame.

                Returns:
                    bool: True if frame exists.
            )doc"
        )
        .def(
            "access_frame_with_name",
            &Manager::accessFrameWithName,
            arg("frame_name"),
            R"doc(
                Access a frame by name.

                Args:
                    frame_name (str): Name of the frame.

                Returns:
                    Frame: Frame with the given name, or None if not found.
            )doc"
        )
        .def(
            "get_all_frame_names",
            &Manager::getAllFrameNames,
            R"doc(
                Get all registered frame names.

                Returns:
                    list[str]: List of all frame names.
            )doc"
        )

        .def(
            "add_frame",
            &Manager::addFrame,
            arg("frame"),
            R"doc(
                Add a frame to the manager.

                Args:
                    frame (Frame): Frame to add.
            )doc"
        )
        .def(
            "remove_frame_with_name",
            &Manager::removeFrameWithName,
            arg("frame_name"),
            R"doc(
                Remove a frame by name.

                Args:
                    frame_name (str): Name of the frame to remove.
            )doc"
        )
        .def(
            "clear_all_frames",
            &Manager::clearAllFrames,
            R"doc(
                Clear all frames from the manager.

                This removes all registered frames and clears the transform cache.
            )doc"
        )

        .def(
            "access_cached_transform",
            &Manager::accessCachedTransform,
            arg("from_frame"),
            arg("to_frame"),
            arg("instant"),
            R"doc(
                Access a cached transform between two frames at a given instant.

                Args:
                    from_frame (Frame): Source frame.
                    to_frame (Frame): Destination frame.
                    instant (Instant): Instant at which the transform is requested.

                Returns:
                    Transform: Cached transform if found, undefined transform otherwise.
            )doc"
        )
        .def(
            "add_cached_transform",
            &Manager::addCachedTransform,
            arg("from_frame"),
            arg("to_frame"),
            arg("instant"),
            arg("transform"),
            R"doc(
                Add a transform to the cache.

                Args:
                    from_frame (Frame): Source frame.
                    to_frame (Frame): Destination frame.
                    instant (Instant): Instant at which the transform applies.
                    transform (Transform): Transform to cache.
            )doc"
        )

        .def_static(
            "get",
            &Manager::Get,
            return_value_policy::reference,
            R"doc(
                Get manager singleton.

                Returns:
                    Manager: Reference to the manager instance.
            )doc"
        )

        ;
}

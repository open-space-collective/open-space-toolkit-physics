/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::type::Integer;
using ostk::core::container::Tuple;
using ostk::core::container::Array;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::Directory;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coord::Frame;
using ostk::physics::data::Vector;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::Unit;
using ostk::physics::units::Length;
using ostk::physics::units::Derived;
using ostk::physics::units::Time;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using EarthGravitationalModelManager = ostk::physics::environment::gravitational::earth::Manager;

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, Constructor)
{
    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::Spherical));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008));

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }

    // Test correct model order and degree combinations

    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        EXPECT_NO_THROW(
            std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Spherical, Directory::Undefined())
        );
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::WGS84, Directory::Undefined(), 20, 0
        ));
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::EGM84, Directory::Undefined(), 180, 180
        ));
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::EGM96, Directory::Undefined(), 360, 360
        ));
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), 2190, 2160
        ));

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }

    // Test incorrect model order and degree combinations

    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::Spherical, Directory::Undefined(), 3000, 3000
        ));

        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::WGS84, Directory::Undefined(), 3000, 3000
        ));
        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::EGM84, Directory::Undefined(), 3000, 3000
        ));
        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::EGM96, Directory::Undefined(), 3000, 3000
        ));
        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(
            EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), 3000, 3000
        ));

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }

    {
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::Spherical,
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        ));

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::WGS84,
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        ));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::EGM84,
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        ));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::EGM96,
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        ));
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::EGM2008,
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        ));
    }

    {
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::Spherical, Directory::Path(Path::Parse("/does/not/exist"))
        ));

        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::WGS84, Directory::Path(Path::Parse("/does/not/exist"))
        ));
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::EGM84, Directory::Path(Path::Parse("/does/not/exist"))
        ));
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::EGM96, Directory::Path(Path::Parse("/does/not/exist"))
        ));
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(
            EarthGravitationalModel::Type::EGM2008, Directory::Path(Path::Parse("/does/not/exist"))
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, IsDefined)
{
    {
        EXPECT_FALSE(EarthGravitationalModel(EarthGravitationalModel::Type::Undefined).isDefined());

        EXPECT_TRUE(EarthGravitationalModel(EarthGravitationalModel::Type::EGM96).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, ParametersFromType)
{
    const Array<Tuple<EarthGravitationalModel::Type, EarthGravitationalModel::Parameters>> testCases = {
        {EarthGravitationalModel::Type::Spherical, EarthGravitationalModel::Spherical},
        {EarthGravitationalModel::Type::WGS84, EarthGravitationalModel::WGS84},
        {EarthGravitationalModel::Type::EGM84, EarthGravitationalModel::EGM84},
        {EarthGravitationalModel::Type::EGM96, EarthGravitationalModel::EGM96},
        {EarthGravitationalModel::Type::EGM2008, EarthGravitationalModel::EGM2008},
    };

    for (const auto& testCase : testCases)
    {
        const EarthGravitationalModel::Type type = std::get<0>(testCase);
        const EarthGravitationalModel::Parameters parameters = std::get<1>(testCase);

        EXPECT_TRUE(parameters == EarthGravitationalModel::ParametersFromType(type));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, Parameters)
{
    {
        EXPECT_EQ(
            EarthGravitationalModel::Spherical,
            EarthGravitationalModel(EarthGravitationalModel::Type::Spherical).getParameters()
        );
        EXPECT_EQ(
            EarthGravitationalModel::WGS84,
            EarthGravitationalModel(EarthGravitationalModel::Type::WGS84).getParameters()
        );
        EXPECT_EQ(
            EarthGravitationalModel::EGM84,
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM84).getParameters()
        );
        EXPECT_EQ(
            EarthGravitationalModel::EGM96,
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM96).getParameters()
        );
        EXPECT_EQ(
            EarthGravitationalModel::EGM2008,
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM2008).getParameters()
        );
    }

    // Spherical
    {
        const EarthGravitationalModel::Parameters parameters = EarthGravitationalModel::Spherical;

        EXPECT_GT(1e-15, parameters.gravitationalParameter_.getValue() - 398600441500000.0);
        EXPECT_GT(1e-15, parameters.equatorialRadius_.inMeters() - 6378137.0);
        EXPECT_GT(1e-15, parameters.flattening_ - 0.0);
        EXPECT_GT(1e-15, parameters.C20_ - 0.0);
        EXPECT_GT(1e-15, parameters.C40_ - 0.0);
        EXPECT_GT(1e-15, parameters.J2_ - 0.0);
        EXPECT_GT(1e-15, parameters.J4_ - 0.0);
    }

    // WGS84
    {
        const EarthGravitationalModel::Parameters parameters = EarthGravitationalModel::WGS84;

        EXPECT_GT(1e-15, parameters.gravitationalParameter_.getValue() - 398600441800000.0);
        EXPECT_GT(1e-15, parameters.equatorialRadius_.inMeters() - 6378137.0);
        EXPECT_GT(1e-15, parameters.flattening_ - 1.0 / 298.257223563);
        EXPECT_GT(1e-15, parameters.C20_ - -4.841668500000e-04);
        EXPECT_GT(1e-15, parameters.C40_ - 5.369958670000e-07);
        EXPECT_GT(1e-15, parameters.J2_ - 0.001082629989051944);
        EXPECT_GT(1e-15, parameters.J4_ - -1.6109876010000001e-06);
    }

    // EGM84
    {
        const EarthGravitationalModel::Parameters parameters = EarthGravitationalModel::EGM84;

        EXPECT_GT(1e-15, parameters.gravitationalParameter_.getValue() - 398600441800000.0);
        EXPECT_GT(1e-15, parameters.equatorialRadius_.inMeters() - 6378137.0);
        EXPECT_GT(1e-15, parameters.flattening_ - 1.0 / 298.257223563);
        EXPECT_GT(1e-15, parameters.C20_ - -4.841668500000e-04);
        EXPECT_GT(1e-15, parameters.C40_ - 5.369958670000e-07);
        EXPECT_GT(1e-15, parameters.J2_ - 0.001082629989051944);
        EXPECT_GT(1e-15, parameters.J4_ - -1.6109876010000001e-06);
    }

    // EGM96
    {
        const EarthGravitationalModel::Parameters parameters = EarthGravitationalModel::EGM96;

        EXPECT_GT(1e-15, parameters.gravitationalParameter_.getValue() - 398600441500000.0);
        EXPECT_GT(1e-15, parameters.equatorialRadius_.inMeters() - 6378136.3);
        EXPECT_GT(1e-15, parameters.flattening_ - 1.0 / 298.257223563);
        EXPECT_GT(1e-15, parameters.C20_ - -4.841653717360e-04);
        EXPECT_GT(1e-15, parameters.C40_ - 5.398738637890e-07);
        EXPECT_GT(1e-15, parameters.J2_ - 0.0010826266835531513);
        EXPECT_GT(1e-15, parameters.J4_ - -1.619621591367e-06);
    }

    // EGM96 + WGS84
    {
        const EarthGravitationalModel::Parameters parameters = EarthGravitationalModel::WGS84_EGM96;

        EXPECT_GT(1e-15, parameters.gravitationalParameter_.getValue() - 398600441800000.0);
        EXPECT_GT(1e-15, parameters.equatorialRadius_.inMeters() - 6378137.0);
        EXPECT_GT(1e-15, parameters.flattening_ - 1.0 / 298.257223563);
        EXPECT_GT(1e-15, parameters.C20_ - -4.841653717360e-04);
        EXPECT_GT(1e-15, parameters.C40_ - 5.398738637890e-07);
        EXPECT_GT(1e-15, parameters.J2_ - 0.0010826266835531513);
        EXPECT_GT(1e-15, parameters.J4_ - -1.619621591367e-06);
    }

    // EGM2008
    {
        const EarthGravitationalModel::Parameters parameters = EarthGravitationalModel::EGM2008;

        EXPECT_GT(1e-15, parameters.gravitationalParameter_.getValue() - 398600441500000.0);
        EXPECT_GT(1e-15, parameters.equatorialRadius_.inMeters() - 6378137.0);
        EXPECT_GT(1e-15, parameters.flattening_ - 1.0 / 298.257223563);
        EXPECT_GT(1e-15, parameters.C20_ - -4.84169317366974e-04);
        EXPECT_GT(1e-15, parameters.C40_ - 5.39965866638991e-07);
        EXPECT_GT(1e-15, parameters.J2_ - 0.0010826355062522235);
        EXPECT_GT(1e-15, parameters.J4_ - -1.6198975999169731e-06);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetType)
{
    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        EXPECT_EQ(
            EarthGravitationalModel::Type::Spherical,
            EarthGravitationalModel(EarthGravitationalModel::Type::Spherical).getType()
        );
        EXPECT_EQ(
            EarthGravitationalModel::Type::WGS84,
            EarthGravitationalModel(EarthGravitationalModel::Type::WGS84).getType()
        );
        EXPECT_EQ(
            EarthGravitationalModel::Type::EGM84,
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM84).getType()
        );
        EXPECT_EQ(
            EarthGravitationalModel::Type::EGM96,
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM96).getType()
        );
        EXPECT_EQ(
            EarthGravitationalModel::Type::EGM2008,
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM2008).getType()
        );

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, Getters)
{
    EarthGravitationalModelManager::Get().setLocalRepository(
        Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
    );

    EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

    {
        EarthGravitationalModel earthGravitationalModel =
            EarthGravitationalModel(EarthGravitationalModel::Type::Spherical);

        EXPECT_FALSE(earthGravitationalModel.getDegree().isDefined());
        EXPECT_FALSE(earthGravitationalModel.getOrder().isDefined());
    }

    {
        const Integer degree = 52;
        const Integer order = 51;

        EarthGravitationalModel earthGravitationalModel =
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM84, Directory::Undefined(), degree, order);

        EXPECT_EQ(earthGravitationalModel.getDegree(), degree);
        EXPECT_EQ(earthGravitationalModel.getOrder(), order);
    }

    {
        const Integer degree = 52;
        const Integer order = 51;

        EarthGravitationalModel earthGravitationalModel =
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM96, Directory::Undefined(), degree, order);

        EXPECT_EQ(earthGravitationalModel.getDegree(), degree);
        EXPECT_EQ(earthGravitationalModel.getOrder(), order);
    }

    {
        const Integer degree = 52;
        const Integer order = 51;

        EarthGravitationalModel earthGravitationalModel =
            EarthGravitationalModel(EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), degree, order);

        EXPECT_EQ(earthGravitationalModel.getDegree(), degree);
        EXPECT_EQ(earthGravitationalModel.getOrder(), order);
    }

    EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository());
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetFieldValueAtNoTruncation)
{
    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        static const Array<Tuple<EarthGravitationalModel::Type, Vector3d, Instant, Vector3d, Real>> testCases = {

            {EarthGravitationalModel::Type::Spherical,
             {6378137.0, 0.0, 0.0},
             Instant::J2000(),
             {-9.79828547181278, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::WGS84,
             {6378137.0, 0.0, 0.0},
             Instant::J2000(),
             {-9.81424104188087, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::EGM84,
             {6378137.0, 0.0, 0.0},
             Instant::J2000(),
             {-9.81430714161684, -2.31935469758198e-05, -1.30080088064139e-05},
             1e-13},
            {EarthGravitationalModel::Type::EGM96,
             {6378137.0, 0.0, 0.0},
             Instant::J2000(),
             {-9.81428438755087, -1.81424333238398e-05, 7.75546781913697e-06},
             1e-13},
            {EarthGravitationalModel::Type::EGM2008,
             {6378137.0, 0.0, 0.0},
             Instant::J2000(),
             {-9.81427987766325, -1.38769560673262e-05, 6.83924677252542e-06},
             1e-13},

            {EarthGravitationalModel::Type::Spherical,
             {7000e3, 0.0, 0.0},
             Instant::J2000(),
             {-8.1347028877551, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::WGS84,
             {7000e3, 0.0, 0.0},
             Instant::J2000(),
             {-8.14569530314416, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::EGM84,
             {7000e3, 0.0, 0.0},
             Instant::J2000(),
             {-8.14574728460001, -2.05387541298693e-05, 2.89745888403438e-05},
             1e-13},
            {EarthGravitationalModel::Type::EGM96,
             {7000e3, 0.0, 0.0},
             Instant::J2000(),
             {-8.14574567850702, -2.19120214388815e-05, 3.01312644719760e-05},
             1e-13},
            {EarthGravitationalModel::Type::EGM2008,
             {7000e3, 0.0, 0.0},
             Instant::J2000(),
             {-8.14574563988817, -2.17632276310511e-05, 2.98622097530464e-05},
             1e-13},

            {EarthGravitationalModel::Type::Spherical,
             {70000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.081347028877551, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::WGS84,
             {70000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.0813481257058837, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::EGM84,
             {70000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.0813481348043554, -3.13557991717857e-09, 1.04503585231838e-10},
             1e-13},
            {EarthGravitationalModel::Type::EGM96,
             {70000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.0813481348016591, -3.14162880220011e-09, 1.03321189670023e-10},
             1e-13},
            {EarthGravitationalModel::Type::EGM2008,
             {70000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.0813481347405648, -3.14187787214874e-09, 1.03341418225995e-10},
             1e-13},

            {EarthGravitationalModel::Type::Spherical,
             {700000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.00081347028877551, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::WGS84,
             {700000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.000813470399061998, 0.0, 0.0},
             1e-13},
            {EarthGravitationalModel::Type::EGM84,
             {700000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.000813470400014733, -3.60438110107890e-13, 5.77106688430063e-16},
             1e-13},
            {EarthGravitationalModel::Type::EGM96,
             {700000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.000813470400014252, -3.61017933053639e-13, 5.21321633031416e-16},
             1e-13},
            {EarthGravitationalModel::Type::EGM2008,
             {700000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.000813470399402024, -3.61045520881784e-13, 5.16916001900846e-16},
             1e-13}

        };

        for (const auto& testCase : testCases)
        {
            const EarthGravitationalModel earthGravitationalModel = {std::get<0>(testCase)};

            const Vector3d position = std::get<1>(testCase);
            const Instant instant = std::get<2>(testCase);

            const Vector3d referenceFieldValue = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Vector3d fieldValue = earthGravitationalModel.getFieldValueAt(position, instant);

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [m.s-2]",
                fieldValue.toString(),
                referenceFieldValue.toString(),
                (fieldValue - referenceFieldValue).norm()
            );
        }

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetFieldValueAtWithTruncation)
{
    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        static const Array<Tuple<EarthGravitationalModel::Type, Integer, Integer, Vector3d, Instant, Vector3d, Real>>
            testCases = {

                {EarthGravitationalModel::Type::WGS84,
                 2,
                 0,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81419735327356, 0.0, 0.0},
                 1e-13},
                {EarthGravitationalModel::Type::EGM84,
                 35,
                 35,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81426334721039, 1.99395502092729e-05, -3.14244321914859e-05},
                 1e-13},
                {EarthGravitationalModel::Type::EGM96,
                 70,
                 70,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81436993747785, -4.31456586427424e-07, -5.07246874662475e-05},
                 1e-13},
                {EarthGravitationalModel::Type::EGM2008,
                 100,
                 100,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81427497884837, -5.76980449670929e-05, -2.2508284743958e-05},
                 1e-13},

                {EarthGravitationalModel::Type::WGS84,
                 4,
                 0,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81424091114504, 0.0, 0.0},
                 1e-13},
                {EarthGravitationalModel::Type::EGM84,
                 60,
                 60,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81437262986811, 2.28752661687178e-05, -6.49048878719256e-05},
                 1e-13},
                {EarthGravitationalModel::Type::EGM96,
                 100,
                 100,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81428102205007, -5.25816746052165e-05, -2.48057498027795e-05},
                 1e-13},
                {EarthGravitationalModel::Type::EGM2008,
                 500,
                 500,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81427466428249, -3.07124249937458e-05, 1.10685209288415e-06},
                 1e-13},

                {EarthGravitationalModel::Type::WGS84,
                 10,
                 0,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81424104188087, 0.0, 0.0},
                 1e-13},
                {EarthGravitationalModel::Type::EGM84,
                 100,
                 100,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81427332735423, -1.85164532971254e-05, -1.44465171851511e-05},
                 1e-13},
                {EarthGravitationalModel::Type::EGM96,
                 250,
                 250,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.8142767596212, 1.05605885798904e-05, -5.71216776245046e-05},
                 1e-13},
                {EarthGravitationalModel::Type::EGM2008,
                 1000,
                 1000,
                 {6378137.0, 0.0, 0.0},
                 Instant::J2000(),
                 {-9.81427696990211, -1.28079338026626e-05, -8.61360014196899e-06},
                 1e-13},

            };

        for (const auto& testCase : testCases)
        {
            const EarthGravitationalModel earthGravitationalModel = {
                std::get<0>(testCase), Directory::Undefined(), std::get<1>(testCase), std::get<2>(testCase)
            };

            const Vector3d position = std::get<3>(testCase);
            const Instant instant = std::get<4>(testCase);

            const Vector3d referenceFieldValue = std::get<5>(testCase);
            const Real tolerance = std::get<6>(testCase);

            const Vector3d fieldValue = earthGravitationalModel.getFieldValueAt(position, instant);

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [m.s-2]",
                fieldValue.toString(),
                referenceFieldValue.toString(),
                (fieldValue - referenceFieldValue).norm()
            );
        }

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetFieldValueAtSTKBenchmark)
{
    {
        EarthGravitationalModelManager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))
        );

        EarthGravitationalModelManager::Get().setMode(EarthGravitationalModelManager::Mode::Automatic);

        // These accelerations were computed in STK using HPOP for the respective model, degree and orders
        static const Array<Tuple<EarthGravitationalModel::Type, Integer, Integer, String, Vector3d, Vector3d, Real>>
            testCases = {

                {EarthGravitationalModel::Type::EGM96,
                 70,
                 70,
                 "2018-01-01T00:00:00",
                 {-1259967.7256766256050, -6885661.5862085318440, 12076.8566057537079},
                 {-8.145654, 0.000044, -0.000047},
                 5e-5},
                {EarthGravitationalModel::Type::EGM96,
                 70,
                 70,
                 "2018-01-01T01:00:00",
                 {-828710.2602364119548, 6063793.4262837288770, -3373594.5811631504512},
                 {5.986840, 3.912014, 3.939528},
                 5e-5},
                {EarthGravitationalModel::Type::EGM2008,
                 100,
                 100,
                 "2018-01-01T00:00:00",
                 {-1259967.7256766256050, -6885661.5862085318440, 12076.8566057537079},
                 {-8.145654, 0.000044, -0.000047},
                 5e-5},
                {EarthGravitationalModel::Type::EGM2008,
                 100,
                 100,
                 "2018-01-01T01:00:00",
                 {-828709.2662392134079, 6063794.1147205904126, -3373594.0636269832029},
                 {5.986841, 3.912013, 3.939527},
                 5e-5},

            };

        for (const auto& testCase : testCases)
        {
            const EarthGravitationalModel earthGravitationalModel = {
                std::get<0>(testCase), Directory::Undefined(), std::get<1>(testCase), std::get<2>(testCase)
            };

            const Instant instant = Instant::DateTime(DateTime::Parse(std::get<3>(testCase)), Scale::UTC);
            const Vector3d position = std::get<4>(testCase);
            const Vector3d referenceFieldValue = std::get<5>(testCase);
            const Real tolerance = std::get<6>(testCase);

            const Vector3d fieldValue = earthGravitationalModel.getFieldValueAt(position, instant);
            const static Unit gravitationalFieldUnit =
                Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second));
            const Vector gravityVector = {fieldValue, gravitationalFieldUnit, Frame::ITRF()};
            const Vector3d fieldValueICRF = gravityVector.inFrame(Frame::GCRF(), instant).getValue();

            EXPECT_TRUE(fieldValueICRF.isNear(referenceFieldValue, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [m.s-2]",
                fieldValueICRF.toString(),
                referenceFieldValue.toString(),
                (fieldValueICRF - referenceFieldValue).norm()
            );
        }

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository(
        ));
    }
}

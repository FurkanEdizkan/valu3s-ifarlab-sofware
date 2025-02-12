^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package diff_drive_controller
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.21.0 (2022-10-21)
-------------------
* std::bind and placeholders instead of boost
* use boost::placeholders::_1/_2 in remaining instances, include boost/bind/bind.hpp instead of boost/bind.hpp, eliminated unnecessary bind.hpp include
* Contributors: Lucas Walter

0.20.0 (2022-05-06)
-------------------
* Drop old C++ standard
* Use new boost bind placeholders
* Add <?xml version=1.0?> to every .launch and .test file
* Contributors: Jochen Sprickerhof, Lucas Walter

0.19.0 (2021-06-13)
-------------------
* fix NaN bug
* fix test to expose NaN bug
* Wait long enough for accumulator to be cleared
* Add test for `#532 <https://github.com/ros-controls/ros_controllers/issues/532>`_
  Close `#540 <https://github.com/ros-controls/ros_controllers/issues/540>`_
* Contributors: Caio Amaral, Matt Reynolds, Melvin Wang

0.18.1 (2020-12-03)
-------------------
* Fix null pointer checks in diff_drive_controller
* Use version-agnostic FindBoost for headers
* Contributors: David V. Lu, Matt Reynolds

0.18.0 (2020-10-11)
-------------------
* Fix dependency on Boost
* Apply consistent format to CMakeLists.txt
* Update package.xml to format 3
* Clean dependencies of diff_drive_controller package
* Apply waitForController method to all diff_drive_controller tests
* Move odom_pub setup to the end to allow consistent isControllerAlive check
* Contributors: Mateus Amarante

0.17.0 (2020-05-12)
-------------------

0.16.1 (2020-04-27)
-------------------

0.16.0 (2020-04-16)
-------------------
* Fix warning dynamic_reconfigure
* Bump CMake version to prevent CMP0048
* Add missing header guards
* Replace header guard with #pragma once
* Prefix every xacro tag with 'xacro:'
* Modernize xacro
  - Remove '--inorder'
  - Use 'xacro' over 'xacro.py'
* switch implementation of read and write methods of Diffbot class
* Refactor nan test
  EXPECT_NE(x, bool) -> EXPECT_TRUE/FALSE(x)
  EXPECT_EQ(x, double) -> EXPECT_DOUBLE_EQ(x, double)
  + clang default reformat
* Check for nan cmd_vel
* Contributors: Anas Abou Allaban, Bence Magyar, Franz, Matt Reynolds, Raffaello Bonghi

0.15.1 (2020-03-09)
-------------------
* Use nullptr
* add missing pluginlib deps.
* Update null link pointer error message
* Revert cmake include catkin_INCLUDE_DIRS as system
* Use C++11 `std::this_thread::sleep_for`.
* Contributors: Bence Magyar, Enrique Fernandez Perdomo, Matt Reynolds, Sean Yen

0.15.0 (2019-03-26)
-------------------
* Default all controller builds to C++14
* boost::chrono -> std::chrono
* boost::assign -> C++ initializer list
* boost::shared_ptr -> std::shared_ptr
* Using left/right multiplies for desired vel
* diff-drive publish joint trajectory controller state
* fix install destination for libraries (`#403 <https://github.com/ros-controls/ros_controllers/issues/403>`_)
* Contributors: Bence Magyar, Gennaro Raiola, James Xu, Jeremie Deray, Jordan Palacios

0.14.3 (2019-02-09)
-------------------
* use operators instead of aliases
* Fix typo descripion -> description
* Contributors: Daniel Ingram, James Xu

0.14.2 (2018-10-23)
-------------------

0.14.1 (2018-06-26)
-------------------
* Added 'multiplier' in DynamicParams ostream and changed boolean printing to 'enabled/disabled'
* isPublishngCmdVelOut to check getNumPublisheres until timeout
* Contributors: Kei Okada, Martin Ganeff

0.14.0 (2018-04-27)
-------------------
* add dynamic_reconf to diff_drive_controller
* migrate to new pluginlib headers
* per wheel radius multiplier
* fix xacro macro warning
* [DiffDrive] Fix time-sensitive tests of diff_drive_controller
* separate include_directories as SYSTEM to avoid unrelated compilation warnings
* Contributors: Jeremie Deray, Mathias Lüdtke

0.13.2 (2017-12-23)
-------------------

0.13.1 (2017-11-06)
-------------------

0.13.0 (2017-08-10)
-------------------
* Add test for allow_multiple_cmd_vel_publishers param
* add check for multiple publishers on cmd_vel
* Added tests for the odom_frame_id parameter.
* Parameterized diff_drive_controller's odom_frame_id
* Publish executed velocity if publish_cmd
* refactor to remove code duplication
* fixup pointer type for new convention
* Allow diff_drive_controller to use spheres as well as cylinders for wheel collision geometry. Cylinders are not well behaved on Gazebo/ODE heightfields, using spheres works around the issue.
* Contributors: Bence Magyar, Eric Tappan, Jeremie Deray, Karsten Knese, Tully Foote, mallanmba, tappan-at-git

0.12.3 (2017-04-23)
-------------------

0.12.2 (2017-04-21)
-------------------

0.12.1 (2017-03-08)
-------------------
* Add exporting include dirs
* Contributors: Bence Magyar

0.12.0 (2017-02-15)
-------------------
* Fix most catkin lint issues
* Change for format2
* Add Enrique and Bence to maintainers
* Add urdf compatibility header
* Add --inorder to xacro calls
* Add missing xacro tags
* Use xacro instead of xacro.py
* Disable angular jerk limit test
* Replace boost::shared_ptr<urdf::XY> with urdf::XYConstSharedPtr when exists
* Contributors: Bence Magyar

0.11.2 (2016-08-16)
-------------------

0.11.1 (2016-05-23)
-------------------

0.11.0 (2016-05-03)
-------------------

0.10.0 (2015-11-20)
-------------------
* Address -Wunused-parameter warnings
* Limit jerk
* Add param velocity_rolling_window_size
* Minor fixes
  1. Coding style
  2. Tolerance to fall-back to Runge-Kutta 2 integration
  3. Remove unused variables
* Fix the following bugs in the testForward test:
  1. Check traveled distance in XY plane
  2. Use expected speed variable on test check
* Add test for NaN
* Add test for bad URDF
* Contributors: Adolfo Rodriguez Tsouroukdissian, Enrique Fernandez, Paul Mathieu

0.9.2 (2015-05-04)
------------------
* Allow the wheel separation and radius to be set from different sources
  i.e. one can be set from the URDF, the other from the parameter server.
  If wheel separation and wheel diameter is specified in the parameter server, don't look them up from urdf
* Contributors: Bence Magyar, Nils Berg

0.9.1 (2014-11-03)
------------------

0.9.0 (2014-10-31)
------------------
* Add support for multiple wheels per side
* Odometry computation:
  - New option to compute in open loop fashion
  - New option to skip publishing odom frame to tf
* Remove dependency on angles package
* Buildsystem fixes
* Contributors: Bence Magyar, Lukas Bulwahn, efernandez

0.8.1 (2014-07-11)
------------------

0.8.0 (2014-05-12)
------------------
* Add base_frame_id param (defaults to base_link)
  The nav_msgs/Odometry message specifies the child_frame_id field,
  which was previously not set.
  This commit creates a parameter to replace the previously hard-coded
  value of the child_frame_id of the published tf frame, and uses it
  in the odom message as well.
* Contributors: enriquefernandez

0.7.2 (2014-04-01)
------------------

0.7.1 (2014-03-31)
------------------
* Changed test-depend to build-depend for release jobs.
* Contributors: Bence Magyar

0.7.0 (2014-03-28)
------------------
* diff_drive_controller: New controller for differential drive wheel systems.
* Control is in the form of a velocity command, that is split then sent on the two wheels of a differential drive
wheel base.
* Odometry is published to tf and to a dedicated nav__msgs/Odometry topic.
* Realtime-safe implementation.
* Implements task-space velocity and acceleration limits.
* Automatic stop after command time-out.
* Contributors: Bence Magyar, Paul Mathieu, Enrique Fernandez.

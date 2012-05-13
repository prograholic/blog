project (boost_bind)


set (BoostBindSources
	my_bind.h
	main.cpp
)

find_package(Boost REQUIRED)


add_executable(boost_bind ${BoostBindSources})
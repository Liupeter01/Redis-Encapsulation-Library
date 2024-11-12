# Redis C++ Encapsulation Library

## Description

using RAII and C++17(optional & string_view)  features to implement a encapsulated redis library 

import hiredis and inifile library

## Developer Quick Start

### Platform Support

Windows, Linux, MacOS(Intel & Apple Silicon M)

### Configure Setting

you need to create a config.ini file in the root directory and pasting this CONFIG_HOME macro to your root CMakeLists

```ini
[Redis]
host=
port=
password=
```

```cmake
target_compile_definitions(redis PUBLIC 
    -DCONFIG_HOME=\"${CMAKE_CURRENT_SOURCE_DIR}/\"
)
```

### Building Library

```bash
git submodule update --init
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel [x]
```

### Example

```c++
  #include<redis/RedisManager.hpp>
  redis::RedisManager::get_instance()->redisObject()->checkAuth("123456");
  redis::RedisManager::get_instance()->redisObject()->setValue("name", "redis");
  redis::RedisManager::get_instance()->redisObject()->setValue("author", "lph");
  redis::RedisManager::get_instance()->redisObject()->setValue("date", "9-8-2024");
  auto res = redis::RedisManager::get_instance()->redisObject()->checkValue("author");
  if (res.has_value()) {
            std::cout << "author = " << res.value();
  }
```


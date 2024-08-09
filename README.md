# Redis C++ Encapsulation Library

## Description

using RAII and C++17(optional & string_view)  features to implement a encapsulated redis library 

import hiredis library as fetchcontent

## Developer Quick Start

### Platform Support

Windows, Linux, MacOS(Intel & Apple Silicon M)

### Configure Setting

you have to change redis host:port and passwd to your own!
```c++
redis::details::RedisManager::RedisManager::RedisManager()
          : RedisManager(std::thread::hardware_concurrency() < 2? 2: std::thread::hardware_concurrency(),
                                   "127.0.0.1",
                                   6379,
                                   "password")
```

### Building Library

```bash
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


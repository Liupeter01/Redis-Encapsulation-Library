#pragma once
#ifndef _REDISTOOLS_HPP_
#define _REDISTOOLS_HPP_
#include<hiredis.h>
#include<optional>
#include<memory>
#include<type_traits>
#include<string>

namespace redis
{
		  class RedisContextWrapper
		  {
		  public:
					RedisContextWrapper(redisContext* ctx)
							  : m_ctx(ctx)
					{}
					redisContext* get() const { return m_ctx; }
					operator redisContext* () const {
							  return get();
					}

		  private:
					redisContext* m_ctx;
		  };

		  template<typename _Ty>
		  struct RedisRAIIDeletor
		  {
					void operator()(_Ty* ptr)
					{
							  if (ptr == nullptr) {
										return;
							  }
							  if constexpr (std::is_same_v<std::decay_t<_Ty>, redisContext>) {
										redisFree(ptr);
							  }
							  else if constexpr (std::is_same_v<std::decay_t<_Ty>, redisReply>) {
										freeReplyObject(ptr);
							  }
							  else {
										delete ptr;
							  }
					}
		  };

		  template<typename _Ty>
		  using RedisRAII = std::unique_ptr<_Ty, RedisRAIIDeletor<_Ty>>;
}

#endif // !_REDISTOOLS_HPP_

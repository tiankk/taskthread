## Introduction
TaskThread is a c++ library for multi-threads programming on windows(xp+) platform.

## Features
* Well wrapped interface.
* Well memory management.
* Integrate with UI thread easily.
* Based on IOCP.
* Task cancel support.

## How to use
### General
1. Add TaskThread Project to your solution.
2. Include `src/task_thread_export.h`.
3. Modify `tthread::THREAD_ID` enum in `src/const_define.h` to add new static thread id.  
	Sample:   
	Original enum:   	
	```cpp
	namespace tthread
	{
		enum THREAD_ID
		{
			STATIC_THREAD_START,  // add static thread id below
			DEFAULT,
			STATIC_THREAD_END, // add static thread id above
			RUNONCE = 1024
		};
	}
	```
	Add `USER_DEF`:
	```cpp
	namespace tthread
	{
		enum THREAD_ID
		{
			STATIC_THREAD_START,  // add static thread id below
			DEFAULT,
			USER_DEF,
			STATIC_THREAD_END, // add static thread id above
			RUNONCE = 1024
		};
	}
	```

4. Call `tthread::AsyncTask()`.
	1. Pass your function/method to `tthread::Bind()`, build task object for task parameter of `tthread::AsyncTask()`.
	2. Set another parameters if necessary. For instance, thread id parameter decide which thread will be run the task. You have defined one or more in step 3. 
5. Build and run your exe. The function/method you passed to the `tthread::Bind()` will be run in the static thread referenced by thread id you have defined and passed to.

### `tthread::Bind()`
1. This Bind() function comes from chromium.
2. The max number of parameters is **7**.
3. Declaring `tthread::utility::Callback<>` or `tthread::utility::Closure` to get return value is no necessary generally. Just pass `tthread::Bind()` to `tthread::AsyncTask()` or `tthread::SyncTask()` as one parameter directly. In general, namespace `tthread::utility` is not used.

Sample:   
* Bind function:   

	```cpp
	int Return5()
	{
		return 5;
	}
	
	tthread::utility::Callback<int(void)> func_cb = tthread::Bind(&Return5);
	LOG(INFO) << func_cb.Run();  // Prints 5.
	
	void PrintHi()
	{
		LOG(INFO) << "hi.";
	}
	
	tthread::utility::Closure void_func_cb = tthread::Bind(&PrintHi);
	void_func_cb.Run();  // Prints: hi.
	```

* Bind method of reference-counted class:
	```cpp
	class Ref : public tthread::RefCountedThreadSafe<Ref> {
	public:
		int Foo() { return 3; }
		void PrintBye() { LOG(INFO) << "bye."; }
	};
	
	tthread::ScopedRefPtr<Ref> ref = new Ref();
	tthread::utility::Callback<int(void)> ref_cb = tthread::Bind(&Ref::Foo, ref.get());
	LOG(INFO) << ref_cb.Run();  // Prints out 3.
	
	tthread::utility::Closure void_ref_cb = tthread::Bind(&Ref::PrintBye, ref.get());
	void_ref_cb.Run();  // Prints: bye.
	```

* Bind method:
**WARNING**: Must be sure object's lifecycle is long enough to run its method. 
	```cpp
	class NoRef {
	public:
		int Foo() { return 4; }
		void PrintWhy() { LOG(INFO) << "why???"; }
	};
	
	NoRef no_ref;
	tthread::utility::Callback<int(void)> no_ref_cb = tthread::Bind(&NoRef::Foo, tthread::Unretained(&no_ref));
	LOG(INFO) << ref_cb.Run();  // Prints out 4.
	
	tthread::utility::Closure void_no_ref_cb = tthread::Bind(&NoRef::PrintWhy, tthread::Unretained(&no_ref));
	void_no_ref_cb.Run();  // Prints: why???
	```

* Bind reference:
	```cpp
	int Identity(int n) { return n; }
	int value = 1;
	tthread::utility::Callback<int(void)> bound_copy_cb = tthread::Bind(&Identity, value);
	tthread::utility::Callback<int(void)> bound_ref_cb = tthread::Bind(&Identity, tthread::ConstRef(value));
	LOG(INFO) << bound_copy_cb.Run();  // Prints 1.
	LOG(INFO) << bound_ref_cb.Run();  // Prints 1.
	
	value = 2;
	LOG(INFO) << bound_copy_cb.Run();  // Prints 1.
	LOG(INFO) << bound_ref_cb.Run();  // Prints 2.
	```

* Curry func:
	```cpp
	int Sum(int a, int b, int c)
	{
		return a + b + c;
	}
	
	tthread::utility::Callback<int(int, int)> sum3_cb = tthread::Bind(&Sum, 3);
	LOG(INFO) << sum3_cb.Run(4, 5);  // Prints 12.
	
	tthread::utility::Callback<int(int)> sum7_cb = tthread::Bind(&Sum, 3, 4);
	LOG(INFO) << sum7_cb.Run(10);  // Prints 17.
	```

### Asynchronous callback
1. There are two callback type according to which thread will be run the callback function.
	1. If callback function run in **task thread**, you should derive from `tthread::IAsyncRunnableTaskCallback`.
	2. If callback funciton run in **UI thread**, you should derive form `tthread::IAsyncRunnableMsgCallback`.
	3. Implement `void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier)` function. `ret` is return value. And you can distinguish invoke point by `identifier`.   
	
	Sample:   
	```cpp
	class UserTaskCallBack : public tthread::IAysncRunnableTaskCallback
	{
	public:
		void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier)
		{
			if(identifier == _T("get_value"))
			{
				if (ret->default_ret_ == 123)
				{
					// do something
				}
			}
		}
	}
	```
2. Wrap your function/method to support return value.
	1. The return type of the wrapped function is `void`.
	2. If function/method have many parameters, return value parameter **must be** the last one.
	3. The **max** number of parameters is **7**. But, **do not** forget that `this` pointer is the first parameter for method. So the max number of parameters for method is **6**.
	4. `tthread::ReturnValue` **should not** wrapped by `tthread::ScopedRefPtr`, if so, callback function running in UI thread may be crash.   

	Sample:   

	Original function:
	```cpp
	int get_value()
	{
		return 123;
	}
	```
   
	Wrapped function:
	```cpp
	void async_get_value(tthread::ReturnValue * ret)
	{
		ret.default_ret_ = get_value();
	}
	```

3. Build wrapped function `async_get_value` to task by `tthread::Bind()` and pass it to `thread::AsyncTask()`.  Also, pass callback object pointer or smart pointer object to `thread::AsyncTask()`.   
	Sample:
	```cpp
	tthread::ScopedRetPtr<UserTaskCallBack> user_task_callback = new UserTaskCallBack;
	
	// some logic
	
	tthread::AsyncTask<tthread::ReturnValue>(_T("get_value"), tthread::Bind(async_get_value), tthread::USER_DEF, user_task_callback.get());
	``` 

4. `tthread::IAsyncRunnableTaskCallback` support smart pointer, so it is safe after you call `tthread::AysncTask()`.
5. `tthread::IAsyncRunnableMsgCallback` **does not** support smart pointer, so you should insure that callback object lifecycle is long enough until callback function is called. Why it does not support? Because this callback object is usually the main window object, tthread should not manage its lifecycle. Of course, if it is not the main window object, you can make it support smart pointer, just derived from `tthread::RefCountedThreadSafe`.

### User-defined return value type
1. Three return value types(ReturnValue/StringReturnValue/IntReturnValue) are already in library. See `src/return_value_type.h`   
2. User can define new type by derived from `tthread::ReturnValue`.   

	Sample:   

	```cpp
	struct UserType
	{
		// some members
	};

	struct UserTypeReturnValue : public tthread::ReturnValue
	{
		UserType user_;
	};
	```
3. In wrapped function/method or callback function `OnAsyncComplete()`, you should cast `tthread::ReturnValue` pointer to `UserTypeReturnValue` pointer.   

	Sample:   

	```cpp
	UserTypeReturnValue* p = static_cast<UserTypeReturnValue*>(ret.get());
	```
4. When you call `tthread::Bind()`, you should **never** create `UserTypeReturnValue` object and pass the pointer to `tthread::Bind()`. TaskThread will create it automatically. Just like the sample below.
   
	Sample:
	```cpp
	tthread::Bind(async_get_value);
	```


### User-defined context parameter type
1. Sometimes, context parameters are stored for refering in callback function or using in whatever logic.   
	Sample:   
	One int value should be stored.   
	```cpp
	struct IntReturnParam : public tthread::ReturnParam
	{
		int stored_int_;
	}
	```

	Wrapped function:
	```cpp
	void async_get_value(tthread::ScopedRefPtr<tthread::ReturnParam> param, ReturnValue* ret)
	{
		ret.param_ = param;
		ret.default_ret_ = get_value();
	}
	```

	Call `tthread::AsyncTask()`:
	```cpp
	tthread::ScopedRetPtr<UserTaskCallBack> user_task_cb = new UserTaskCallBack;

	// some logic

	IntReturnParam* p = new IntReturnParam;
	p->stored_int_ = 1234;
	tthread::AsyncTask<UserTypeReturnValue>(_T("user_logic"), tthread::Bind(aysnc_get_value, p), tthread::USER_DEF, user_task_cb.get());
	```

	Use context parameter in callback function:
	```cpp
	class UserTaskCallBack : public tthread::IAysncRunnableTaskCallback
	{
	public:
		void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier)
		{
			if(identifier == _T("user_logic"))
			{
				IntReturnParam* param = static_cast<IntReturnParam>(ret->param_.get())
				if (param->stored_int_ == 1234)
				{
					// some logic
				}
			}
		}
	}
	```

2. Again, You should **never** create and pass the return value object pointer to `tthread::Bind()`.
3. The context parameter pointer passed to `tthread::AysncTask()` will be recycle automatilcally. **Do not** delele it by yourself.

### Integrate with UI thread
1. As said in [Asynchronous callback](#Asynchronous callback), if callback class is derived from `tthread::IAsyncRunnableMsgCallback` and its instance is initiated in UI thread(main thread), callback function will run in UI thread(main thread).
	Sample:
	```cpp
	class UserMsgCallback : public tthread::IAsyncRunnableMsgCallback
	{
		void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier)
		{
			// some logic
		}
	}
	
	// some logic
	
	UserMsgCallback user_msg_callback; // in UI thread(main thread)
	
	// some logic
	
	tthread::AsyncTask<tthread::ReturnValue>(_T("get_value"), tthread::Bind(async_get_value), tthread::USER_DEF, &user_msg_callback);
	
	```
Again, as said in [Asynchronous callback](#Asynchronous callback), `tthread::AsyncRunnableMsgCallback` **does not** support smart pointer, you should manage lifecycle of callback objcet and make sure it is exist when callback function is called.
2. Also, you can use `tthread::AsyncMessage()` interface to send `tthread::ReturnValue` object or other user-defined return value object to the UI thread(main thread) directly, without triggering callback function by one task. The `tthread::ReturnValue` object here is just one message.

### `tthread::RUNONCE` thread
1. There are two types thread, one is static thread, the another is runonce thread.
2. **Static threads** can referened by `tthread::THREAD_ID`. You can get it everywhere during whole lifecycle by `tthread::THREAD_ID`.
3. **Runonce threads** just run one task every time. You can never insure that the runonce thread you get this time is the one you have got last time. 
4. All runonce threads managed in a thread pool. The threads in sleep state will be reused next time.

### `tthread::AsyncMessage()`
[Integrate with UI thread](#Integrate with UI thread) has mentioned that you can send message to trigger callback function in UI thread. Except that, you also can send message to task thread. It is depending on the type of callback object. See [Asynchronous callback](#Asynchronous callback).
Sample:
```cpp
class UserMsgCallback : public tthread::IAsyncRunnableMsgCallback
{
	void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier)
	{
		// some logic
	}
}

// some logic

UserMsgCallback user_msg_callback; // in UI thread(main thread)

// some logic

tthread::ReturnValue* msg = new tthread::ReturnValue;
msg.default_ret_ = 123;
tthread::AsyncMessage(_T("this_is_a_msg"), msg, &user_msg_callback);
```
```cpp
class UserTaskCallback : public tthread::IAsyncRunnableTaskCallback
{
	void OnAsyncComplete(ScopedRefPtr<ReturnValue> ret, const tstring& identifier)
	{
		// some logic
	}
}

// some logic

tthread::ScopedRefPtr<UserTaskCallback> user_task_callback = new UserTaskCallback;

// some logic

tthread::ReturnValue* msg = new tthread::ReturnValue;
msg.default_ret_ = 123;
tthread::AsyncMessage(_T("this_is_a_msg"), msg, user_task_callback.get(), tthread::USER_DEF);
```
**Do not** delete message by yourself. It will be recycled automatically.

Again, as said in [Asynchronous callback](#Aysnchronous callback), `tthread::AsyncRunnableMsgCallback` **does not** support smart pointer, you should manage lifecycle of callback objcet and make sure it is exist when callback function is called.

### `tthread::SyncTask()`
If you want to run task in other thread then wait for it in invoke thread, you should use this interface. When task finishes, `tthread::SyncTask()` will return `tthread::ScopedRefPtr<tthread::ReturnValue>` object directly.

### Quit
* There are two interfaces for quit: `tthread::SafeQuit()` and `tthread::SafeEmergencyQuit()`.
* Once you invoke one of two, you **can not** send tasks to the task queue managed by IOCP.
* `tthread::SafeQuit()` quit all threads after all tasks in queue have been run.
* `tthread::SafeEmergencyQuit()` quit all threads without running tasks in queue.

## Common use elements
Details about these elements, please read source code.
### Header
`src/task_thread_export.h`

### Namespace
`tthread`

### Function
```cpp
tthread::Bind()

tthread::AsyncTask()

template <typename ReturnValueType>
tthread::AsyncTask<ReturnValueType>()
   
tthread::AsyncMessage()

tthread::SyncTask()

template <typename ReturnValueType>
tthread::SyncTask<ReturnValueType>()
```   
### Base Class
```cpp
tthread::ReturnValue

tthread::ReturnParam

tthread::IAsyncRunnableCallbackBase

tthread::IAsyncRunnableMsgCallback

tthread::IAsyncRunnableTaskCallback
```
### Enum
```cpp
tthread::THREAD_ID
```
### Utils
```cpp
tthread::RefCountedThreadSafe

tthread::StringReturnValue

tthread::IntReturnValue

tthread::ScopedRefPtr

tthread::ScopedPtr

template <typename T>
tthread::Unretained()

template <typename T>
tthread::ConstRef()

template <typename T>
tthread::IgnoreResult()
```
# Demo
See demo project.

# Feedback
Send mail to <tiankk@gmail.com>.

# License
MIT

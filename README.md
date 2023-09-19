# info
That is a preview version. I just have started and I am going to improve this logger. 
# usage

```cpp
int main() {
	try { // tbh i almost haven't used exceptions but i guess i will
		auto p = make_handler<console_handler_basic<char>>();
		logger_basic<char> logger(p);
		logger.log("hello world");
	}
	catch (std::exception& e) {
		std::cout << "exception:" << e.what() << std::endl;
	}
}
```

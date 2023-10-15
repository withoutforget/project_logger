# info
That is a preview version. I just have started and I am going to improve this logger. 
# usage

```cpp
int main() {
	try {
		auto p = make_handler<basic_console_handler<std::u16string>>();
		basic_logger<std::u16string> logger(p);
		logger.log(u"Привет мир");
	}
	catch (std::exception& e) {
		std::cout << "exception:" << e.what() << std::endl;
	}
}
```

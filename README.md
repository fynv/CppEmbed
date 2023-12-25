# CppEmbed

This is doing the same thing as the [V8AndGUI](https://github.com/fynv/V8AndGUI) demo, except that no scripting engine is used, and everything is in C++.

The "scripting" code are compiled into DLLs, which can be dynamically loaded at runtime.

APIs are wrapped and exported first using extern "C", then wrapped again using a set of header-only classes, which are derived from std::shared_ptr.

This is just like a typical plugin pattern, so nothing much to say.

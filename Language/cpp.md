##cpp

####类型转换

1. static_cast<new_type>(expression): 接近于C风格转换， 无关类的类指针之间转换有安全性提升
2. dynamic_cast<new_type>(expression): 确保指针的转换是合适完整的,new_type为指针或者引用,
下行转换基类是多态的， 对于不安全的下行转换将返回空指针，当目标指针是void指针时dynamic_cast
总是认为安全的。
3. reinterpret_cast<new_type>(expression)重解释转换, 两个没有任何关系的类指针之间的转换, 这
个转换是最不安全的
4. const_cast<new_type>(expression)常量向非常量转换,这个转换并不转换原常量本事，只是返回的结果是
非常量。



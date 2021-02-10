#ifndef FT_CONTAINERS_CONSTVECTORITERATOR_HPP
#define FT_CONTAINERS_CONSTVECTORITERATOR_HPP

namespace ft {
	template <typename T>
	class ConstVectorIterator {
	private:
		T *ptr_;
	public:
		ConstVectorIterator() {};
		ConstVectorIterator(const ConstVectorIterator &c) {
			*this = c;
		}
		ConstVectorIterator (T *p) : ptr_(p) {}
		virtual ~ConstVectorIterator() {}
		const T &operator* () {
			return (*ptr_);
		}
		const T *operator->() {
			return (*ptr_);
		}
		ConstVectorIterator &operator++ () {
			ptr_++;
			return *this;
		}
		ConstVectorIterator operator++ (int) {
			ConstVectorIterator tmp = *this;
			ptr_++;
			return tmp;
		}
		ConstVectorIterator &operator-- () {
			ptr_--;
			return *this;
		}
		ConstVectorIterator operator-- (int) {
			ConstVectorIterator tmp = *this;
			ptr_--;
			return tmp;
		}
		ConstVectorIterator &operator= (const ConstVectorIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ConstVectorIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ConstVectorIterator& other) const {
			return ptr_ != other.ptr_;
		}
		ConstVectorIterator operator+(const ConstVectorIterator& other) const {
			ConstVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + other.ptr_;
			return tmp;
		}

		ConstVectorIterator operator+(const int incr) const {
			ConstVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + incr;
			return tmp;
		}
		ConstVectorIterator operator-(const ConstVectorIterator& other) const {
			ConstVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - other.ptr_;
			return tmp;
		}
		ConstVectorIterator operator-(const int &other) const {
			ConstVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - other;
			return tmp;
		}
		bool operator<(const ConstVectorIterator& other) {
			return (ptr_ < other.ptr_);
		}
		bool operator<=(const ConstVectorIterator& other) {
			return (ptr_ <= other.ptr_);
		}
		bool operator>(const ConstVectorIterator& other) {
			return (ptr_ > other.ptr_);
		}
		bool operator>=(const ConstVectorIterator& other) {
			return (ptr_ >= other.ptr_);
		}
		ConstVectorIterator operator+=(const ConstVectorIterator& other) {
			ptr_ += other.ptr_;
			return ptr_;
		}
		ConstVectorIterator operator+=(int other) {
			ptr_ += other;
			return ptr_;
		}
		ConstVectorIterator operator-=(const ConstVectorIterator& other) {
			ptr_ -= other.ptr_;
			return ptr_;
		}
		ConstVectorIterator operator-=(int other) {
			ptr_ -= other;
			return ptr_;
		}
		const T &operator[](int n){
			return (*(ptr_ + n));
		}
	};
}

#endif

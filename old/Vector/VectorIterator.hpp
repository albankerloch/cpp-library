#ifndef FT_CONTAINERS_VECTORITERATOR_HPP
#define FT_CONTAINERS_VECTORITERATOR_HPP

namespace ft {
	template <typename T>
	class VectorIterator {
	private:
		T *ptr_;
	public:
		VectorIterator() {};
		VectorIterator(const VectorIterator &c) {
			*this = c;
		}
		VectorIterator (T *p) : ptr_(p) {}
		virtual ~VectorIterator() {}
		T &operator* () {
			return (*ptr_);
		}
		T *operator->() {
			return (*ptr_);
		}
		VectorIterator &operator++ () {
			ptr_++;
			return *this;
		}
		VectorIterator operator++ (int) {
			VectorIterator tmp = *this;
			ptr_++;
			return tmp;
		}
		VectorIterator &operator-- () {
			ptr_--;
			return *this;
		}
		VectorIterator operator-- (int) {
			VectorIterator tmp = *this;
			ptr_--;
			return tmp;
		}
		VectorIterator &operator= (const VectorIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const VectorIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const VectorIterator& other) const {
			return ptr_ != other.ptr_;
		}
		VectorIterator operator+(const VectorIterator& other) const {
			VectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + other.ptr_;
			return tmp;
		}

		VectorIterator operator+(const int incr) const {
			VectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + incr;
			return tmp;
		}
		VectorIterator operator-(const VectorIterator& other) const {
			VectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - other.ptr_;
			return tmp;
		}
		VectorIterator operator-(const int &other) const {
			VectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - other;
			return tmp;
		}
		bool operator<(const VectorIterator& other) {
			return (ptr_ < other.ptr_);
		}
		bool operator<=(const VectorIterator& other) {
			return (ptr_ <= other.ptr_);
		}
		bool operator>(const VectorIterator& other) {
			return (ptr_ > other.ptr_);
		}
		bool operator>=(const VectorIterator& other) {
			return (ptr_ >= other.ptr_);
		}
		VectorIterator operator+=(const VectorIterator& other) {
			ptr_ += other.ptr_;
			return ptr_;
		}
		VectorIterator operator+=(int other) {
			ptr_ += other;
			return ptr_;
		}
		VectorIterator operator-=(const VectorIterator& other) {
			ptr_ -= other.ptr_;
			return ptr_;
		}
		VectorIterator operator-=(int other) {
			ptr_ -= other;
			return ptr_;
		}
		T &operator[](int n){
			return (ptr_[n]);
		}
	};
}

#endif //FT_CONTAINERS_VECTORITERATOR_HPP

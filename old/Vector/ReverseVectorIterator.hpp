#ifndef FT_CONTAINERS_REVERSEVECTORITERATOR_HPP
#define FT_CONTAINERS_REVERSEVECTORITERATOR_HPP

namespace ft {
	template <typename T>
	class ReverseVectorIterator {
	private:
		T *ptr_;
	public:
		ReverseVectorIterator() {};
		ReverseVectorIterator(const ReverseVectorIterator &c) {
			*this = c;
		}
		ReverseVectorIterator (T *p) : ptr_(p) {}
		virtual ~ReverseVectorIterator() {}
		T &operator* () {
			return (*ptr_);
		}
		T *operator->() {
			return (*ptr_);
		}
		ReverseVectorIterator &operator++ () {
			ptr_--;
			return *this;
		}
		ReverseVectorIterator operator++ (int) {
			ReverseVectorIterator tmp = *this;
			ptr_--;
			return tmp;
		}
		ReverseVectorIterator &operator-- () {
			ptr_++;
			return *this;
		}
		ReverseVectorIterator operator-- (int) {
			ReverseVectorIterator tmp = *this;
			ptr_++;
			return tmp;
		}
		ReverseVectorIterator &operator= (const ReverseVectorIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ReverseVectorIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ReverseVectorIterator& other) const {
			return ptr_ != other.ptr_;
		}
		ReverseVectorIterator operator+(const ReverseVectorIterator& other) const {
			ReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - other.ptr_;
			return tmp;
		}

		ReverseVectorIterator operator+(const int incr) const {
			ReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - incr;
			return tmp;
		}
		ReverseVectorIterator operator-(const ReverseVectorIterator& other) const {
			ReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + other.ptr_;
			return tmp;
		}
		ReverseVectorIterator operator-(const int &other) const {
			ReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + other;
			return tmp;
		}
		bool operator<(const ReverseVectorIterator& other) {
			return (ptr_ > other.ptr_);
		}
		bool operator<=(const ReverseVectorIterator& other) {
			return (ptr_ >= other.ptr_);
		}
		bool operator>(const ReverseVectorIterator& other) {
			return (ptr_ < other.ptr_);
		}
		bool operator>=(const ReverseVectorIterator& other) {
			return (ptr_ <= other.ptr_);
		}
		ReverseVectorIterator operator+=(const ReverseVectorIterator& other) {
			ptr_ -= other.ptr_;
			return ptr_;
		}
		ReverseVectorIterator operator+=(int other) {
			ptr_ -= other;
			return ptr_;
		}
		ReverseVectorIterator operator-=(const ReverseVectorIterator& other) {
			ptr_ += other.ptr_;
			return ptr_;
		}
		ReverseVectorIterator operator-=(int other) {
			ptr_ += other;
			return ptr_;
		}
		T &operator[](int n){
			return (*(ptr_ - n));
		}
	};
}

#endif //FT_CONTAINERS_VECTORITERATOR_HPP

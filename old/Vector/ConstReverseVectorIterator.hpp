#ifndef FT_CONTAINERS_CONSTREVERSEVECTORITERATOR_HPP
#define FT_CONTAINERS_CONSTREVERSEVECTORITERATOR_HPP

namespace ft {
	template <typename T>
	class ConstReverseVectorIterator {
	private:
		T *ptr_;
	public:
		ConstReverseVectorIterator() {};
		ConstReverseVectorIterator(const ConstReverseVectorIterator &c) {
			*this = c;
		}
		ConstReverseVectorIterator (T *p) : ptr_(p) {}
		virtual ~ConstReverseVectorIterator() {}
		const T &operator* () {
			return (*ptr_);
		}
		const T *operator->() {
			return (*ptr_);
		}
		ConstReverseVectorIterator &operator++ () {
			ptr_--;
			return *this;
		}
		ConstReverseVectorIterator operator++ (int) {
			ConstReverseVectorIterator tmp = *this;
			ptr_--;
			return tmp;
		}
		ConstReverseVectorIterator &operator-- () {
			ptr_++;
			return *this;
		}
		ConstReverseVectorIterator operator-- (int) {
			ConstReverseVectorIterator tmp = *this;
			ptr_++;
			return tmp;
		}
		ConstReverseVectorIterator &operator= (const ConstReverseVectorIterator &other){
			ptr_ = other.ptr_;
			return (*this);
		}
		bool operator== (const ConstReverseVectorIterator& other) const {
			return ptr_ == other.ptr_;
		}
		bool operator!= (const ConstReverseVectorIterator& other) const {
			return ptr_ != other.ptr_;
		}
		ConstReverseVectorIterator operator+(const ConstReverseVectorIterator& other) const {
			ConstReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - other.ptr_;
			return tmp;
		}

		ConstReverseVectorIterator operator+(const int incr) const {
			ConstReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ - incr;
			return tmp;
		}
		ConstReverseVectorIterator operator-(const ConstReverseVectorIterator& other) const {
			ConstReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + other.ptr_;
			return tmp;
		}
		ConstReverseVectorIterator operator-(const int &other) const {
			ConstReverseVectorIterator tmp = *this;
			tmp.ptr_ = ptr_ + other;
			return tmp;
		}
		bool operator<(const ConstReverseVectorIterator& other) {
			return (ptr_ > other.ptr_);
		}
		bool operator<=(const ConstReverseVectorIterator& other) {
			return (ptr_ >= other.ptr_);
		}
		bool operator>(const ConstReverseVectorIterator& other) {
			return (ptr_ < other.ptr_);
		}
		bool operator>=(const ConstReverseVectorIterator& other) {
			return (ptr_ <= other.ptr_);
		}
		ConstReverseVectorIterator operator+=(const ConstReverseVectorIterator& other) {
			ptr_ -= other.ptr_;
			return ptr_;
		}
		ConstReverseVectorIterator operator+=(int other) {
			ptr_ -= other;
			return ptr_;
		}
		ConstReverseVectorIterator operator-=(const ConstReverseVectorIterator& other) {
			ptr_ += other.ptr_;
			return ptr_;
		}
		ConstReverseVectorIterator operator-=(int other) {
			ptr_ += other;
			return ptr_;
		}
		const T &operator[](int n){
			return (*(ptr_ - n));
		}
	};
}

#endif //FT_CONTAINERS_VECTORITERATOR_HPP

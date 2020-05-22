#include "BiArray.h"


// default constructor - Initialise empty array (first time)
BiArray::BiArray() {
  arrSize_ = 0;
  capacity_ = INITIALCAP;
  internalArr_ = new int [capacity_];
  position_ = INITIALCAP/2;
}

// value constructor - Resize the internal array if needed.
// add elements from the passed array to newly created array.
BiArray::BiArray(int arr[], int size)  {
  arrSize_ = size;
  if (LO_THRESHOLD*arrSize_ > INITIALCAP){
    capacity_ = LO_THRESHOLD*arrSize_;
  }else{
    capacity_ = INITIALCAP;
  }
  internalArr_ = new int[capacity_];
  position_ = (capacity_ - arrSize_)/2;
  for(int i=0; i < arrSize_; i++){
    internalArr_[position_ + i] = arr[i];
  }
}

// destructor - delete internal array to free up memory resources.
BiArray::~BiArray() {
  delete [] internalArr_;
}

// copy constructor - create new array object by initialising it with an previously created object
// i.e. creating a copy  
BiArray::BiArray(const BiArray& other) {
  arrSize_ = other.arrSize_;
  capacity_ = other.capacity_;
  position_ = other.position_;
  internalArr_ = new int[capacity_];
  for(int i = 0; i < capacity_; i++){
    internalArr_[i] = other.internalArr_[i];
  }
}

// move constructor - Moves resources from one object to another
//deletes other variables to free up resources once moved
BiArray::BiArray(BiArray&& other) {
  internalArr_ = other.internalArr_;
  arrSize_ = other.arrSize_;
  capacity_ = other.capacity_;
  position_ = other.position_;
  other.internalArr_ = nullptr;
  other.arrSize_ = 0;
  other.capacity_ = 0;
  other.position_ = 0;
}

// copy assignment - Used with the copy constructor to carry out the copy.
// Ensuring the copy is only completed for other array objects.
BiArray& BiArray::operator=(const BiArray& other) {
  
  if(this != &other){
    if(arrSize_ != other.arrSize_){
      delete [] internalArr_;
      capacity_ = other.capacity_;
      arrSize_ = other.arrSize_;
      position_ = other.position_;
      internalArr_ = new int [other.capacity_];
    }
    for(int i = 0; i < capacity_; i++){
      internalArr_[i] = other.internalArr_[i];
    }
    return *this;
  }
}

// move assignment - Used by the move constructor to carry out the move using temp variables.
BiArray& BiArray::operator=(BiArray&& other) {
  if(this != &other){
    int* temp_arr = internalArr_;
    internalArr_ = other.internalArr_;
    other.internalArr_ = temp_arr;

    int temp_arrSize = arrSize_;
    arrSize_ = other.arrSize_;
    other.arrSize_ = temp_arrSize;

    int temp_capacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = temp_capacity;

    int temp_position = position_;
    position_ = other.position_;
    other.position_ = temp_position;
  }
  return *this;
}

//Assign value at position i to the variable v.
bool BiArray::get(int i, int& v) const {
  if (i >=  0 && i < arrSize_){
    v = internalArr_[position_ + i];
    return true;
  }else{
    return false;
  }
}

//Take value v and assign it to a different position i.
bool BiArray::set(int i, int v) {
  if (i >= 0 && i < arrSize_){
    internalArr_[position_ + i] = v;
    return true;
  }else{
    return false;
  }
}

//Allow array index accessing for int
int BiArray::operator[](int i) const {
  return internalArr_[position_ + i];
}
//Allow array index accessing for int&
int& BiArray::operator[](int i) {
  return internalArr_[position_ + i];
}
//Insert element v at the back of the array in the first empy space
//Resize the array if there is not enough room to do so
void BiArray::push_back(int v) {
  if ((position_ + arrSize_) == capacity_){
    capacity_ = LO_THRESHOLD*arrSize_;
    int temp_arr[arrSize_];
    for (int i = 0; i < arrSize_; i++){
      temp_arr[i] = internalArr_[position_ + i];
    }
    position_ = (capacity_ - arrSize_)/2;
    delete [] internalArr_;
    internalArr_ = new int[capacity_];
    for (int i = 0; i < arrSize_; i++){
      internalArr_[position_ + i] = temp_arr[i];
    }
  }
  internalArr_[position_ + arrSize_] = v;
  arrSize_ += 1;
}
//Remove element at the back of the array
//Resize array if the empy space becomes more than 5 times array size
bool BiArray::pop_back() {
  if (arrSize_ == 0){
    return false;
  }
  if (capacity_ > (HI_THRESHOLD*arrSize_)){
      capacity_ = LO_THRESHOLD*arrSize_;
  }
  arrSize_ -= 1;
  int temp_arr[arrSize_];
  for (int i = 0; i < arrSize_; i++){
    temp_arr[i] = internalArr_[position_ + i];
  }
  position_ = (capacity_ - arrSize_)/2;
  delete [] internalArr_;
  internalArr_ = new int[capacity_];
  for (int i = 0; i < arrSize_; i++){
    internalArr_[position_ + i] = temp_arr[i];
  }
    return true;
}
//Insert element at the first empty space at the front of the array.
//Resize array if there is not space to do so
void BiArray::push_front(int v) {
  if (position_ == 0){
    capacity_ = LO_THRESHOLD*arrSize_;
    int temp_arr[arrSize_];
    for (int i = 0; i < arrSize_; i++){
      temp_arr[i] = internalArr_[position_ + i];
    }
    position_ = (capacity_ - arrSize_)/2;
    delete [] internalArr_;
    internalArr_ = new int[capacity_];
    for (int i = 0; i < arrSize_; i++){
      internalArr_[position_ + i] = temp_arr[i];
    }
  }
  internalArr_[position_ - 1] = v;
  arrSize_ += 1;
  position_ -= 1;
}

//Remove element from front of array
//Resize if there is not room to do so
bool BiArray::pop_front() {
  if (arrSize_ == 0){
    return false;
  }
  if (capacity_ > (HI_THRESHOLD*arrSize_)){
      capacity_ = LO_THRESHOLD*arrSize_;
  }
  arrSize_ -= 1;
  position_ += 1;
  int temp_arr[arrSize_];
  for (int i = 0; i < arrSize_; i++){
    temp_arr[i] = internalArr_[position_ + i];
  }
  position_ = (capacity_ - arrSize_)/2;
  delete [] internalArr_;
  internalArr_ = new int[capacity_];
  for (int i = 0; i < arrSize_; i++){
    internalArr_[position_ + i] = temp_arr[i];
  }
    return true;
}

int BiArray::getSize() const {
  return arrSize_;
  
}

int BiArray::getCapacity() const {
  return capacity_;
} 

//Print formatted internal array e.g [1 2 3 4]
string BiArray::print() const {
  string intArrStr_ = "";
  for (int i = 0; i < arrSize_; i++){
    intArrStr_ += to_string(internalArr_[i + position_]);
    if( i != arrSize_ -1){
      intArrStr_ += " ";
    }
   }
  string formatArr_ = "[" + intArrStr_ + "]";
   return formatArr_;
}

string BiArray::printAll() const {
         
         // NOT IMPLEMENTED (Optional)
	// below are just stub code
	string removeMe = "";
	return removeMe;
}

//Compare each element of two arrays to determine if they are the same size (and order)
bool operator==(const BiArray& lhs, const BiArray& rhs) {
  int lhSize_ = lhs.getSize();
  int rhSize_ = rhs.getSize();
  bool result_ = false;
  if(lhSize_ == 0 && rhSize_ == 0){
    return true;
  }
  if(lhSize_ == rhSize_){
      for (int i = 0; i < lhSize_; i++){
	if(lhs.internalArr_[lhs.position_ + i] == rhs.internalArr_[rhs.position_ + i]){
	  result_ = true;
	}else{
	  return false;
	}
      }
      return result_;
  }
  return false;
}

//Compare two arrays and determine if they are NOT equal
//Affected by size and order of the array
bool operator!=(const BiArray& lhs, const BiArray& rhs) {
  int lhSize_ = lhs.getSize();
  int rhSize_ = rhs.getSize();
  bool result_ = false;
  if(lhSize_ == 0 && rhSize_ == 0){
    return false;
  }
  if(lhSize_ == rhSize_){
      for (int i = 0; i < lhSize_; i++){
	if(lhs.internalArr_[lhs.position_ + i] == rhs.internalArr_[rhs.position_ + i]){
	  result_ = false;
	}else{
	  return true;
	}
      }
      return result_;
  }
  return true;
}


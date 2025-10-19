#ifndef LIST_H
#define LIST_H

template <typename T> 
class List {
    public:
        virtual void insert(int pos, T e){
		pos = e;
		if(0>pos && pos>size()){
			std::out_of_range;
		}
	}
	
	virtual void append(T e){
		while(pos != size()+1){
		 pos++
		}
       		insert();
	}

	virtual void prepend(T e){
		if(pos==0){
			insert();
		}
	}

	T remove(int pos){
		 if(0>pos && pos>size()){
                        std::out_of_range;
                }
		int i=getchar(pos);
		return i;
		delete i;
	}

	T remove(int pos){
                 if(0>pos && pos>size()){
                        std::out_of_range;
                }
                int i=getchar(pos);
		return i;
	}

	int search(T e){
		while(getchar(pos) != e){
			pos++;
		}
		retun pos;
		if(pos=size()+1){
			return -1;
		}

	bool empty(){
		if(size()=0){
			return false;
		} else{
			return true;
		}
	}
	
	int size(){
		size= getsize(T);
		return size;
	}	

};

#endif

///*this program is working!!!!!!!!!!*///


#include <iostream>

template <typename T>
class provector
{
    T* array;
    int size;
    int private_size;
    double growth_rate;
    int first;
    int mode; // 1: pb   2: n   3: pf

public :
    provector(std::string Mode = "pb", int First_Size = 8, double Growth_Rate = 2.00)
    {
        if(Growth_Rate < 1.5 )
        {
            Growth_Rate = 2;
            std::cerr << "warning : growth rate should be 1.5 or greater\nIt has been automatically set to 2.00" << std::endl;
        }

        if(Mode == "pb") this->mode = 1;
        else if(Mode == "n") this->mode = 2;
        else if(Mode == "pf") this->mode = 3;
        else {this->mode = 2; std::cerr << Mode << " is not defined as a provector mode!(\"pb\", \"pf, or \"n\")\nmode will be automatically set to Normal mode" << std::endl;}

        this->array = new T[First_Size];
        this->size = 0;
        this->private_size = First_Size;
        this->growth_rate = Growth_Rate;

        if(this->mode == 1) this->first = 0;
        else if(this->mode == 2) this->first = int(this->private_size/2);
        else if(this->mode == 3) this->first = this->private_size - 1;
        else {this->first = int(this->private_size/2); std::cerr << "something happened during calculating this->first" << std::endl;}


    }
    provector& push_back(T data)
    {
        if(this->size == 0)
        {
            this->array[this->first] = data;
            this->size ++;
            return *this;
        }

        if(this->mode == 3)
        {
            if(this->size < this->private_size)
            {
                std::cerr << "warning in line : push_front_fast_mode is on\nuse recommended functions to change mode\n";

                for(int i=this->first; i<this->first + this->size; i++)
                {
                    this->array[i-1] = this->array[i];
                }
                this->array[this->first + this->size - 1] = data;
                this->size ++;
                this->first --;
            }
            else
            {
                int new_size = int(this->private_size * this->growth_rate);
                T* temp = new T[new_size];
                for(int i=1; i<=this->size; i++)
                {
                    temp[new_size-i] = this->array[this->first + this->size - i];
                }
                temp[this->size + 1] = data;

                /// this is an important bug to fix later!!!
//                std::cout << "hello from pushback!!!\tloop ended";
                delete [] this->array;
//                std::cout << "hello from pushback!!!\tdelete is done";
                this->array = temp; //change with main array
                this->private_size = new_size;
                this->first = new_size - this->size;

            }

            return *this;
        }

        ///if mode != pf :
        if(this->first + this->size < this->private_size)
        {
            this->array[first + size] = data;
            this->size += 1 ;
            return *this;
        }
        else
        {
            T *temp = new T[int(this->private_size * this->growth_rate)]; // new array
            for (int i = first; i < first + size; ++i) {
                temp[i] = this->array[i]; // copy everything
            }

            delete[]this->array;
            this->array = temp; //change with main array
            this->private_size = int(this->private_size * this->growth_rate);
            this->push_back(data);
            return *this;
        }

    }
    void operator<<(T data)
    {
        this->push_back(data);
    }

    provector& push_front(T data)
    {
        if(this->size == 0)
        {
            this->array[this->first] = data;
            this->size ++;
            return *this;
        }

        if(this->mode == 1)
        {
            if(this->size < this->private_size)
            {
                std::cerr << "warning in line : push_back_fast_mode is on\nuse recommended functions to change mode\n";

                for(int i=this->first+this->size-1; i>=this->first; i--)
                {
                    this->array[i+1] = this->array[i];
                }
                this->array[this->first] = data;
                this->size ++;
                return *this;
            }
            else
            {
                int new_size = int(this->private_size * this->growth_rate);
                T* temp = new T[new_size];
                for(int i=this->first; i<=this->first+this->size; i++)
                {
                    temp[i+1] = this->array[i];
                }
                temp[this->first] = data;

                delete []this->array;
                this->array = temp; //change with main array
                this->private_size = new_size;
                this->size ++;
                return *this;
            }

            return *this;
        }

        ///if mode != pb :
        else
        {
            if (this->first > 0) {
                this->array[this->first - 1] = data;
                this->size++;
                this->first--;
                return *this;
            } else {
                int new_size = int(this->private_size * this->growth_rate);
                T *temp = new T[new_size]; // new array
                for (int i = this->first; i < this->first + this->size; i++) {
                    temp[i + new_size - this->private_size] = this->array[i]; // copy everything
                }
                delete[]this->array;
                this->array = temp; //change with main array
                this->first = this->first + new_size - this->private_size;
                this->private_size = new_size;
                this->push_front(data);
                return *this;
            }
        }
    }
    friend void operator>>(T data, provector& pv)
    {
        pv.push_front(data);
    }

    void change_mode(int m)
    {
        if(m == 1)
        {
            /// if there is no need to change
            if(this->mode == 1) return;

            /// if the first data is not in index zero
            for(int i=this->first; i<this->first + this->size; i++)
            {
                this->array[i - this->first] = this->array[i];
            }

            /// change mode is done
            this->mode = 1;
            this->first = 0;
            return;
        }
        else if(m == 2)
        {
            /// copy everything to temp
            T* temp = new T[this->size];
            for(int i=this->first; i<this->first + this->size; i++)
            {
                temp[i - this->first] = this->array[i];
            }
            this->first = (this->private_size - this->size) / 2;

            /// everything back to main array
            for(int i=this->first; i<this->first + this->size; i++)
            {
                this->array[i] = temp[i - this->first];
            }

            /// change mode is done
            this->mode = 2;
            return;
        }
        else if(m == 3)
        {
            /// if there is no need to change
            if(this->mode == 3) return;

            /// if last data is not in index private_size - 1
            for(int i=this->first + this->size - 1, j=this->private_size - 1; i>=this->first; i--, j--)
            {
                this->array[j] = this->array[i];
            }

            /// change mode is done
            this->mode = 3;
            this->first = this->private_size - this->size;
            return;
        }
        else
        {
            std::cerr << "invalid mode" << std::endl;
            return;
        }
    }

    void change_mode(std::string m)
    {
        if(m == "pb" || m == "push back")
        {
            this->change_mode(1);
            return;
        }
        if(m == "n" || m == "normal")
        {
            this->change_mode(2);
            return;
        }
        if(m == "pf" || m == "push front")
        {
            this->change_mode(3);
            return;
        }
        else
        {
            this->change_mode(4);
            return;
        }
    }

    int get_size()
    {
        return this->size;
    }

    int get_memory_usage()
    {
        return this->private_size;
    }

    int get_mode()
    {
        return this->mode;
    }

    int get_first()
    {
        return this->first;
    }

    void print(std::string sep = ", ")
    {
        if(this->size == 0)
        {
            std::cout << "[]";
            return;
        }

        std::cout << "[";
        for(int i=this->first; i<this->first + this->size - 1; i++)
        {
            std::cout << this->array[i] << sep;
        }
        std::cout << this->array[this->first + this->size - 1] << "]";
    }

    friend std::ostream& operator<< (std::ostream& os, provector<T>& v)
    {
        v.print();
        return os;
    }


};



int main() {
    provector<int> pv("pb", 4, 2);
    std::cout << "first : " << pv.get_first() << std::endl;

    for(int i=3; i<15; i++)
    {
        pv.push_front(i);
        if(i == 7) pv.change_mode(3);
        std::cout << pv << "  size : " << pv.get_size() << "  private size : " <<
        pv.get_memory_usage() << "  mode : " << pv.get_mode() << "  first : " << pv.get_first() << std::endl;
    }

//    std::cout << pv << "  size : " << pv.get_size() << "  private size : " << pv.get_memory_usage() << "  mode : " << pv.get_mode() << std::endl;


    return 0;
}


#include "state.h"
#include <string>

state::state( std::initializer_list< unsigned int > init )
: sticks(init)
{
   
}

state::state( unsigned int i1, unsigned int i2 )
{
   for(int i = i1; i <= i2; i++)
   {
    sticks.push_back(i);
   
   }
}

unsigned int state::sum( ) const
{
   int sum = 0;
   for(int i = 0; i < sticks.size(); i++)
   {
      sum += sticks[i];
   }
   return sum;
}

optional_move state::randommove( ) const 
{
   if(sum() == 0)
   {
      return optional_move();
   }

   int rand_row, rand_remaining;
   rand_row = rand() % sticks.size();

   while(sticks[rand_row] == 0)
   {
      rand_row = rand() % sticks.size();
   }
   
   rand_remaining = rand() % sticks[rand_row];
   return move(rand_row, rand_remaining);


}

void state::make( move m )
{
  if(m.row < sticks.size() && (m.row + 1) > 0 )
  {
    sticks[m.row] = m.remaining;
  }
  else
  {
    std::cout << "Aborted";
    std::abort();
  }

}

void state::print( std::ostream& out ) const
{

   int j = 0;

   for(int i = 0; i < sticks.size(); i++)
   {
      std::cout << i + 1 << " " << ":" << " ";
      for(int k = 0; k < sticks[j]; k++)
      {
         std::cout << 1 << " ";
      }

      std::cout << " \n";
      j++;
   }
}




optional_move state::removelastmorethantwo () const 
{
   int sticks_counter = 0, one_counter = 0, index; 
   for(int i = 0; i < sticks.size(); ++i) {
      if(sticks[i] > 1) {
         sticks_counter++;
         index = i;
      }
      if(sticks[i] == 1) one_counter++;
   }

   if(sticks_counter != 1) 
     return optional_move();

   if(one_counter % 2 != 0) 
     return move(index, 0);
   
   else 
     return move(index, 1);
}


unsigned int state::nimber() const
{
    unsigned int num = 0;
    for (size_t i = 0; i < sticks.size(); i++)
        num ^= sticks[i];
    return num;
}

optional_move state::makenimberzero() const
{
    unsigned int num = nimber();
    if (num == 0)
        return optional_move();

    bool found = false;
    for (size_t i = 0; !found && i < sticks.size(); i++)
    {
        int i_num = sticks[i];
        for (size_t rem = 0; rem < i_num; rem++)
        {
            num = nimber();
            if (num == 0)
            {
                return move(i, rem);
                found = true;
                break;
            }
        }
    }
    return optional_move();
}


optional_move state::usermove( std::ostream& out, std::istream& in ) const
{

   if( sum( ))
   {
      while( true )
      {
         std::string inp;
         try
         {
            out << "row? "; out. flush( );
            in >> inp; 

            unsigned int row = std::stoul( inp ); inp. clear( );

            if( row > 0 && row <= sticks. size( )) 
            {
               unsigned int row1 = row - 1;  // This is a type conversion! 
               if( sticks[ row1 ] )
               {
                  out << "how many remaining? "; out. flush( );
                  in >> inp; 
                  unsigned int remain = std::stoul( inp ); inp. clear( ); 

                  if( remain < sticks[ row1 ] )
                     return move( row1, remain );
                  else
                  {
                     out << "having " << remain 
                         << " remaining is not possible, "
                         << "you have to remove at least one stick\n";
                  }
               }
               else 
               {
                  out << "row " << row << " is already empty\n";
               }
            }
            else
            {
               out << "row " << row << " is not a valid row, ";
               out << "rows are between 1 and " << sticks. size( ) << "\n";
            }
            
         }
         catch( std::invalid_argument& inv )
         {
            out << inp << " is not a number\n";
         }
         catch( std::out_of_range& r )
         {
            out << inp << " is too big\n";
         }
      }
   }
   else
      return optional_move( ); 
}



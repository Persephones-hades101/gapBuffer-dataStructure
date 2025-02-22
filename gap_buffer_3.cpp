#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void resizeBuffer(vector<char> &buffer, int &gap_start, int &gap_end)
{
  // a b c _ d e f ---> a b c _ d e f _ _ _ _ _ _ _ ---> a b c _ _ _ _ _ _ _ _ d e f
  int obs = buffer.size();
  int counter = obs - 1 - (gap_end + 1) + 1;

  // double the buffer size
  buffer.resize(buffer.size() * 2, '_');
  int nbs = buffer.size();
  gap_end = nbs - counter - 1; // new gap is before 'd' (in above example) in final array
  while (counter--)
  {
    // cout << "counter " << counter << endl;
    // cout << buffer[obs - (counter)] << endl;
    buffer[nbs - (counter + 1)] = buffer[obs - (counter + 1)];
    buffer[obs - (counter + 1)] = '_';
  }
}

void printBuffer(vector<char> &v)
{
  for (int i = 0; i < v.size(); i++)
  {
            cout << v[i] << " ";

  }

  cout << endl;
}

string printText(vector<char> &v)
{
  string text = "";
  bool found = false;
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i] != '_')
    {
      text = text + v[i];
    }
    if(!found && v[i] == '_'){
        found = true;
        text = text + '|';
    }

  }
  return text;
}

void insert_in_buffer(vector<char> &buffer, int &gap_start, int &gap_end, char x)
{
  if (gap_start == gap_end)
  {
    resizeBuffer(buffer, gap_start, gap_end);
  }
  buffer[gap_start] = x;
  gap_start++;
}

void move_cursor_left(vector<char> &buffer, int &gap_start, int &gap_end)
{
  if (gap_start == 0)
    return;
  buffer[gap_end] = buffer[gap_start - 1];
  gap_start--;
  gap_end--;
  buffer[gap_start] = '_';
}
void move_cursor_right(vector<char> &buffer, int &gap_start, int &gap_end)
{
  if (gap_end == buffer.size() - 1)
    return;
  buffer[gap_start] = buffer[gap_end + 1];
  gap_start++;
  gap_end++;
  buffer[gap_end] = '_';
}

void delete_(vector<char> &buffer, int &gap_start)
{
  if (gap_start == 0)
    return;

  buffer[gap_start - 1] = '_';
  gap_start--;
}

void insert_in_buffer_multiple_times(vector<char> &buffer, int &gap_start, int &gap_end)
{
  while (true)
  {
    char x;
    cin.get(x);
    bool double_next_line = false;
    while (x == '\n')
    {
      cin.get(x);
      if (x == '\n')
      {
        double_next_line = true;
        break;
      }
    }
    if (double_next_line)
      break;
    insert_in_buffer(buffer, gap_start, gap_end, x);
    // printBuffer(buffer);
  }
}

//#define TEST
#ifdef TEST
    #include<time.h>
    int main(void)
    {
      vector<char> buffer(7, '_');
      int gap_start = 0;
      int gap_end = buffer.size() - 1;
      srand(time(NULL));
      int round = 10;
      while(round--)
      {

        int idx = rand()%buffer.size();
        if(idx % 2)
        {
            delete_(buffer, gap_start);
          move_cursor_left(buffer, gap_start, gap_end);

        }
        else{
          move_cursor_right(buffer, gap_start, gap_end);

        }
        insert_in_buffer(buffer, gap_start, gap_end,'a' + rand()%26);
        cout << "___________________________________\n";
        printBuffer(buffer); 
        cout << "___________________________________" << endl;


      }

    }
#endif


#ifndef EXPORT_SHARED
int main()
{
  vector<char> buffer(7, '_');
  int gap_start = 0;
  int gap_end = buffer.size() - 1;

  insert_in_buffer_multiple_times(buffer, gap_start, gap_end);
  printBuffer(buffer);
  // cout << gap_start << " " << gap_end << endl;
  // cout << gap_start << " " << gap_end << endl;
  move_cursor_left(buffer, gap_start, gap_end);
  move_cursor_left(buffer, gap_start, gap_end);
  move_cursor_left(buffer, gap_start, gap_end);
  printBuffer(buffer);
  insert_in_buffer_multiple_times(buffer, gap_start, gap_end);
  printBuffer(buffer);
  move_cursor_right(buffer, gap_start, gap_end);
  printBuffer(buffer);
  delete_(buffer, gap_start);
  printBuffer(buffer);
  return 0;
}
#endif 

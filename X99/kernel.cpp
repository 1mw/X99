// X99 Library
namespace xlib
{
	namespace video
	{
		// Address at which the VGA is manipulated
		const int VIDEO_MEMORY = 0xb8000;
		
		const int MAX_COLUMN = 80;
		const int MAX_ROW = 25;
		
		int column = 0;
		int row = 0;
		
		void writeString(const char* string)
		{
			while(*string != 0)
			{
				char* v = (char*) (VIDEO_MEMORY + (((row * 80) + column) * 2));
				*v = *string;
				column++;
				
				if(column >= MAX_COLUMN)
				{
					column = 0;
					row++;
				}
				
				if(row >= MAX_ROW)
				{
					column = 0;
					row = 0;
				}
				
				string++;
			}
		}
		
		void setCursorPosition(int column, int row)
		{
			
		}
		
		void newLine()
		{
			column = 0;
			row++;
			
			if(row >= MAX_ROW)
			{
				row = 0;
			}
		}
	}
	
	namespace misc
	{
		char* itoa(int val, int base) {
			
			if(val == 0)
			{
				return "0";
			}
			
			static char buf[32] = {0};
			
			int i = 30;
			
			for(; val && i ; --i, val /= base)
			
			buf[i] = "0123456789abcdef"[val % base];
			
			return &buf[i+1];
			
		}
	}
}

extern "C"
void kernel_main()
{
	xlib::video::writeString("Welcome to the X99 operating system. It currently generates prime numbers.");
	xlib::video::newLine();
	
	int check = 13;
	while(true)
	{
		bool prime = true;
		for(int i = 3; i < check / 2; i++)
		{
			if(check % i == 0)
			{
				prime = false;
			}
		}
		
		if(prime)
		{
			xlib::video::writeString("Found prime number: ");
			xlib::video::writeString(xlib::misc::itoa(check, 10));
			xlib::video::newLine();
		}
		check += 2;
	}
}
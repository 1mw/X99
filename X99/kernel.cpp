namespace Video
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
}

extern "C"
void kernel_main()
{
	Video::writeString("Hello world from the X99 kernel! ");
	Video::writeString("Hello again! This is demonstrating that the column and row system is working correctly!");
}
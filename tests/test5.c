int	main()
{
	malloc2(1024);
	malloc2(1024 * 32);
	malloc2(1024 * 1024);
	malloc2(1024 * 1024 * 16);
	malloc2(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
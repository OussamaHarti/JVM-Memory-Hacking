namespace GUtils {

    void applyRoundedCorners(System::Windows::Forms::Form^ form, unsigned short radius);

	//Use on mouse down action
	void dragPanelMD(System::Windows::Forms::Form^ form, System::Drawing::Point& pt);

	//Use on mouse move
	void dragPanelMM(System::Windows::Forms::Form^ form, System::Drawing::Point& pt, System::Windows::Forms::MouseEventArgs^ e);
}
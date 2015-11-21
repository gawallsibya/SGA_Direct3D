using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace CS
{
    public partial class MainForm : Form
    {   
        public MainForm()
        {
            InitializeComponent();
            
            foreach (Control c in this.Controls)
            {
                Button b = c as Button;
                if (b == null) continue;
                
                b.Click += new System.EventHandler(this.OnClickButton);
            }

            ui_tbCalc.Text = "(2+(1.0-0.5)*2)";
        }

        bool IsOperator(string sToken)
        {
            if (sToken == "+") return true;
            if (sToken == "-") return true;
            if (sToken == "*") return true;
            if (sToken == "/") return true;
            if (sToken == "(") return true;
            if (sToken == ")") return true;
            return false;
        }

        
        bool IsOperand(ref int nIndex)
        {
	        char c = ui_tbCalc.Text[nIndex];

	        if(c == '+' || c == '*' || c == '/' || c == '(' || c == ')')
		        return false;
	
	        if(c == '.')
		        return true;

	        if(c == '-')
	        {
                if (nIndex != 0 && ui_tbCalc.Text[nIndex - 1] == '(')
			        return true;
		        else 
			        return false;
	        }

	        return true;
        }


        string GetToken(ref int nIndex)
        {
            string sInfix = ui_tbCalc.Text;

	        if(sInfix.Length <= nIndex)
		        return string.Empty;

            string sToken = string.Empty;
	
	
	        while(true)
	        {
		        if(IsOperand(ref nIndex))
		        {
                    sToken += sInfix[nIndex];
			        nIndex++;
		        }
		        else
		        {
                    if (sToken.Length > 0)
			        {
				        break;
			        }
                    sToken += sInfix[nIndex];
			        nIndex++;
			        break;
		        }
	        }

            return sToken;
        }

        float Calculate()
        {
            Hashtable htPriority = new Hashtable();
            htPriority["*"] = 10;
            htPriority["/"] = 10;
            htPriority["+"] = 9;
            htPriority["-"] = 9;
            htPriority["("] = 8;


            List<string> lstPostfix = new List<string>();
            List<string> lstOperatorStack = new List<string>();

            
	        string sInfix = ui_tbCalc.Text;

	        int nIndex = 0;
	        while(true)
	        {
                string sToken = GetToken(ref nIndex);
                if (sToken == string.Empty)
                    break;
		        if(IsOperator(sToken))
		        {
			        if(sToken == "(")
			        {
				        lstOperatorStack.Add(sToken);
			        }
			        else if(sToken == ")")
			        {
				        while(true)
				        {
					        string sOperator = lstOperatorStack[lstOperatorStack.Count - 1];
					        lstOperatorStack.RemoveAt(lstOperatorStack.Count - 1);
					        if(sOperator == "(")
					        {
						        break;
					        }
					        else
					        {
						        lstPostfix.Add(sOperator);
					        }
				        }
			        }
			        else
			        {
				        while(true)
				        {
					        string sCurrOperator = sToken;
					        string sTopOperator = lstOperatorStack[lstOperatorStack.Count - 1];

					        if((int)htPriority[sTopOperator] < (int)htPriority[sCurrOperator])
					        {
						        lstOperatorStack.Add(sCurrOperator);
						        break;
					        }
					        else
					        {
						        lstPostfix.Add(sTopOperator);
						        lstOperatorStack.RemoveAt(lstOperatorStack.Count - 1);
					        }
				        }
			        }
		        }
		        else
		        {
			        lstPostfix.Add(sToken);
		        }
	        }
            
	        List<float> lstCalcStack = new List<float>();

	        for (int i = 0; i < lstPostfix.Count; ++i)
	        {
		        if(IsOperator(lstPostfix[i]))
		        {
			        float v1 = lstCalcStack[lstCalcStack.Count - 1];
			        lstCalcStack.RemoveAt(lstCalcStack.Count - 1);
			        
                    float v2 = lstCalcStack[lstCalcStack.Count - 1];
			        lstCalcStack.RemoveAt(lstCalcStack.Count - 1);

			        float v = 0.0f;
			        if(lstPostfix[i] == "+")
			        {
				        v = v2 + v1;
			        }
			        else if(lstPostfix[i] == "-")
			        {
				        v = v2 - v1;
			        }
			        else if(lstPostfix[i] == "*")
			        {
				        v = v2 * v1;
			        }
			        else if(lstPostfix[i] == "/")
			        {
				        v = v2 / v1;
			        }
			        lstCalcStack.Add(v);
		        }
		        else
		        {
			        lstCalcStack.Add(float.Parse(lstPostfix[i]));
		        }
	        }

            return lstCalcStack[0];
        }

        private void OnClickButton(object sender, EventArgs e)
        {
            Button b = sender as Button;
            if(b == null)
                return;

            if (b.Text == "←")
            {
                if (ui_tbCalc.Text.Length > 0)
                {
                    ui_tbCalc.Text = 
                        ui_tbCalc.Text.Remove(ui_tbCalc.Text.Length - 1);
                }
                
            }
            else if (b.Text == "CE")
            {
                ui_tbCalc.Text = string.Empty;
            }
            else if (b.Text == "=")
            {
                ui_tbCalc.Text = Calculate().ToString();
            }
            else
            {
                ui_tbCalc.Text += b.Text;
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ManagedTest
{
    public partial class frmMngExc : Form
    {
        public frmMngExc()
        {
            InitializeComponent();
        }

        private void btnExc_Click(object sender, EventArgs e)
        {
            //System.Exception ex = new System.Exception("Managed Exception");
            //throw ex;
            var obj = new object();
            obj = null;
            MessageBox.Show(obj.ToString());
        }

        private void btnExcHnd_Click(object sender, EventArgs e)
        {
            try { 
                
                throw new System.Exception("Managed Exception"); 
            }
            catch (System.Exception ex) 
            { 
                MessageBox.Show(ex.Message);             
            }
        }
    }
}

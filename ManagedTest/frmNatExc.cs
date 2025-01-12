using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ManagedTest
{
    public partial class frmNatExc : Form
    {

        [DllImport("Cases.dll", EntryPoint = "AccessViolate", CallingConvention = CallingConvention.Cdecl)]
        public static extern void AccessViolate();
        public frmNatExc()
        {
            InitializeComponent();
        }

        private void btnAV_Click(object sender, EventArgs e)
        {
            AccessViolate();
        }
    }
}

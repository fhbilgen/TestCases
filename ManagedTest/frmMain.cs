﻿using System;
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
    public partial class frmMain : Form
    {
  
        public frmMain()
        {
            InitializeComponent();
        }

        private void testsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmMemoryTests frmMem = new frmMemoryTests();
            frmMem.ShowDialog();
        }

        private void nativeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmNatExc frmNatExc = new frmNatExc();
            frmNatExc.ShowDialog();
        }
    }
}

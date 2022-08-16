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
    public partial class frmMemoryTests : Form
    {
        public frmMemoryTests()
        {
            InitializeComponent();
        }

        public void RefreshActiveObjects()
        {
            txtNumOfObj.Text = MemoryConsumer._objList.Count.ToString();
        }
        private void btnAdd_Click(object sender, EventArgs e)
        {
            string strHowMany = "";
            int howMany = 0;

            Cursor.Current = Cursors.WaitCursor;
            strHowMany = txtAdd.Text;
            int.TryParse(strHowMany, out howMany);
            MemoryConsumer.GrowList(howMany);
            RefreshActiveObjects();
            Cursor.Current = Cursors.Arrow;
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            string strHowMany = "";
            int howMany = 0;

            Cursor.Current = Cursors.WaitCursor;
            strHowMany = txtRemove.Text;
            int.TryParse(strHowMany, out howMany);
            MemoryConsumer.ShrinkList(howMany);
            RefreshActiveObjects();
            Cursor.Current = Cursors.Arrow;
        }

        private void btnGCCollect_Click(object sender, EventArgs e)
        {
            GC.Collect();
        }
    }
}

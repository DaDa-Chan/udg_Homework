
echo "--- Personal Diary Test Script ---"

# --- Cleanup ---
echo "[INFO] Removing any existing diary file..."
rm -f personal_diary.dat

# --- pdadd ---
echo ""
echo "[TEST] Adding initial entries using pdadd..."

# Use a "here document" (<< EOF) to provide multi-line input to pdadd
./pdadd 2025-04-07 << EOF
ajjdajdj
ndjjsancoac
cnakjncoac
.
EOF

./pdadd 2025-04-06 << EOF
asnckna
ackcjjcoav
klcnosqc
.
EOF

./pdadd 2025-04-08 << EOF
nacjkacac
ckalckakcow
jncaoeeqo
cakcoke
.
EOF

echo "[INFO] Added 3 entries."

# --- pdlist ---
echo ""
echo "[TEST] Listing all entries using pdlist..."
./pdlist

echo ""
echo "[TEST] Listing entries for a specific date (2025-04-07) using pdlist..."
./pdlist 2025-04-07 2025-04-07

echo ""
echo "[TEST] Listing entries in a range (2025-04-06 to 2025-04-07) using pdlist..."
./pdlist 2025-04-06 2025-04-07

# --- pdshow ---
echo ""
echo "[TEST] Showing content for 2025-04-07 using pdshow..."
./pdshow 2025-04-07

echo ""
echo "[TEST] Attempting to show content for non-existent date (2025-04-09)..."
./pdshow 2025-04-09 # Expect an error message on stderr

# --- pdremove ---
echo ""
echo "[TEST] Removing entry for 2025-04-06 using pdremove..."
./pdremove 2025-04-06
# Check the exit code ($? holds the exit code of the last command)
if [ $? -eq 0 ]; then
  echo "[INFO] pdremove succeeded for 2025-04-05 (Exit Code: 0)"
else
  echo "[WARN] pdremove failed or entry not found for 2025-04-06 (Exit Code: $?)"
fi

echo ""
echo "[TEST] Attempting to remove non-existent entry (2025-04-05)..."
./pdremove 2025-04-05
if [ $? -eq 0 ]; then
  echo "[WARN] pdremove unexpectedly succeeded for 2025-04-05 (Exit Code: 0)"
elif [ $? -eq 255 ]; then # Bash often represents -1 as 255
  echo "[INFO] pdremove correctly reported entry not found for 2025-04-05 (Exit Code: $? -> interpreted as -1)"
else
  echo "[INFO] pdremove failed as expected for 2004-04-05 (Exit Code: $?)"
fi


# --- Overwrite/Replace ---
echo ""
echo "[TEST] Replacing entry for 2025-04-08 using pdadd..."
./pdadd 2025-04-08 << EOF
12342422
1344124
.
EOF
echo "[INFO] Replaced entry for 2025-04-08."

echo ""
echo "[TEST] Showing updated content for 2025-04-08..."
./pdshow 2023-10-28

# --- Final State ---
echo ""
echo "[TEST] Listing final entries..."
./pdlist

echo ""
echo "--- Test Script Finished ---"

exit 0
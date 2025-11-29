import express from 'express';
import Book from '../models/Book.js';

const router = express.Router();

// Get all books
router.get('/', async (req, res) => {
  try {
    const books = await Book.find().populate('seller', 'fullName');
    res.json(books);
  } catch (err) {
    res.status(500).json({ message: 'Server error' });
  }
});

// Add a book (Seller only - simplified auth check for now)
router.post('/', async (req, res) => {
  try {
    const { title, author, price, category, sellerId } = req.body;
    
    const newBook = new Book({
      title,
      author,
      price,
      category,
      seller: sellerId
    });

    const book = await newBook.save();
    res.status(201).json(book);
  } catch (err) {
    res.status(500).json({ message: 'Server error', error: err.message });
  }
});

export default router;

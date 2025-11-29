import mongoose from 'mongoose';
import dotenv from 'dotenv';
import bcrypt from 'bcryptjs';
import User from './models/User.js';
import Book from './models/Book.js';

dotenv.config();

const seedData = async () => {
  try {
    // Connect to MongoDB
    await mongoose.connect(process.env.MONGO_URI);
    console.log('✅ Connected to MongoDB');

    // Clear existing data
    await User.deleteMany({});
    await Book.deleteMany({});
    console.log('🧹 Cleared existing data');

    // Create a Demo Seller
    const salt = await bcrypt.genSalt(10);
    const hashedPassword = await bcrypt.hash('password123', salt);

    const seller = await User.create({
      fullName: 'Demo Seller',
      email: 'seller@example.com',
      password: hashedPassword,
      role: 'seller'
    });
    console.log('👤 Created Demo Seller (email: seller@example.com, pass: password123)');

    // Create a Demo Customer
    const customer = await User.create({
      fullName: 'Demo Customer',
      email: 'customer@example.com',
      password: hashedPassword,
      role: 'customer'
    });
    console.log('👤 Created Demo Customer (email: customer@example.com, pass: password123)');

    // Create Sample Books
    const books = [
      {
        title: 'The Great Gatsby',
        author: 'F. Scott Fitzgerald',
        price: 12.99,
        category: 'Classic',
        cover: '🍸',
        rating: 4.8,
        seller: seller._id
      },
      {
        title: 'Atomic Habits',
        author: 'James Clear',
        price: 16.99,
        category: 'Self-Help',
        cover: '⚛️',
        rating: 4.9,
        seller: seller._id
      },
      {
        title: 'Dune',
        author: 'Frank Herbert',
        price: 14.99,
        category: 'Sci-Fi',
        cover: '🏜️',
        rating: 4.7,
        seller: seller._id
      },
      {
        title: 'Project Hail Mary',
        author: 'Andy Weir',
        price: 18.99,
        category: 'Sci-Fi',
        cover: '🚀',
        rating: 4.9,
        seller: seller._id
      },
      {
        title: 'The Psychology of Money',
        author: 'Morgan Housel',
        price: 15.50,
        category: 'Finance',
        cover: '💰',
        rating: 4.8,
        seller: seller._id
      },
      {
        title: 'Clean Code',
        author: 'Robert C. Martin',
        price: 29.99,
        category: 'Technology',
        cover: '💻',
        rating: 4.6,
        seller: seller._id
      }
    ];

    await Book.insertMany(books);
    console.log(`📚 Added ${books.length} sample books`);

    console.log('✨ Seeding completed successfully!');
    process.exit(0);
  } catch (error) {
    console.error('❌ Error seeding data:', error);
    process.exit(1);
  }
};

seedData();
